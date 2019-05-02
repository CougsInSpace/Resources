//AGI Java API
import agi.core.*;
import agi.stkutil.*;
import agi.stkvgt.IAgCrdnEventIntervalSmartInterval;
import agi.stkobjects.*;

public class SampleCode
{
	private AgStkObjectRootClass	m_AgStkObjectRootClass;

	/* package */SampleCode(AgStkObjectRootClass root)
	throws AgCoreException
	{
		this.m_AgStkObjectRootClass = root;
	}

	/*package*/ static String getReportName(String satName, String sensorName)
	{
		StringBuffer sb = new StringBuffer();

		String dir = System.getProperty("user.dir");
		String fileSep = System.getProperty("file.separator");

		sb.append(dir);

		if(!dir.endsWith(fileSep))
		{
			sb.append(fileSep);
		}

		sb.append(satName);
		sb.append("_");
		sb.append(sensorName);
		sb.append("_");
		sb.append(System.currentTimeMillis());
		sb.append(".txt");

		return sb.toString();
	}

	/* package */void createScenario()
	throws Throwable
	{
		try
		{
			this.m_AgStkObjectRootClass.closeScenario();
			this.m_AgStkObjectRootClass.newScenario("GfxAnalysis");

			this.m_AgStkObjectRootClass.getUnitPreferences().setCurrentUnit("DistanceUnit", "km");
			this.m_AgStkObjectRootClass.getUnitPreferences().setCurrentUnit("DateFormat", "UTCG");

			AgScenarioClass scen = null;
			scen = (AgScenarioClass)this.m_AgStkObjectRootClass.getCurrentScenario();

			// ======================================
			// Create the satellite
			// ======================================
			String satName = "Sat1";
			IAgStkObjectCollection scenChildren = scen.getChildren();
			AgSatelliteClass sat = null;
			sat = (AgSatelliteClass)scenChildren._new(AgESTKObjectType.E_SATELLITE, satName);
			
			// ======================================
			// Set the scale value for the Model
			// to be near real life.
			// ======================================
			String sep = System.getProperty("file.separator");
			String userDir = System.getProperty("user.dir");
			StringBuffer sb = new StringBuffer();
			sb.append(userDir);
			sb.append(sep);
			sb.append("data");
			sb.append(sep);
			sb.append("satellite.mdl");

			IAgSaVO satVo = sat.getVO();
			IAgSaVOModel satVoModel = satVo.getModel();
			IAgVOModelFile mdlFile = (IAgVOModelFile)satVoModel.getModelData();
			mdlFile.setFilename(sb.toString());
			satVoModel.setScaleValue(0.0);

			// ======================================
			// Set the propagator to two body
			// ======================================
			sat.setPropagatorType(AgEVePropagatorType.E_PROPAGATOR_TWO_BODY);
			IAgVePropagatorTwoBody twobody = null;
			twobody = (IAgVePropagatorTwoBody)sat.getPropagator();

			// ======================================
			// Set the propagation start/stop time
			// ======================================
			IAgCrdnEventIntervalSmartInterval interval = null;
			interval = twobody.getEphemerisInterval();
			interval.setExplicitInterval(scen.getStartTime(), scen.getStopTime());
			twobody.setStep(60.0);

			// ====================================
			// Convert to a classical orbit state
			// ====================================
			IAgVeInitialState initState = twobody.getInitialState();
			IAgOrbitState os = initState.getRepresentation();
			os.setEpoch(scen.getStartTime());
			os.assignClassical(AgECoordinateSystem.E_COORDINATE_SYSTEM_J2000, 6878.14, 0.0, 45.0, 0.0, 0.0, 0.0);

			// ===================================================================
			// Now propagate the twobody classical J2000 coordinate system orbit
			// ===================================================================
			twobody.propagate();

			//===============================
			// Create the sensor
			//===============================
			
			IAgStkObjectCollection satChildren = sat.getChildren();
			
			IAgSensor sensor = null;
			sensor = (IAgSensor)satChildren._new(AgESTKObjectType.E_SENSOR, "Sensor1");
			
			IAgSnVO vo = sensor.getVO();
			IAgSnVOOffset offset = vo.getVertexOffset();

			offset.setInheritFromParentObj(false);
			offset.setEnableTranslational(true);
			offset.setAxisOffsetValue(AgEAxisOffset.E_SENSOR_RADIUS, 0);
			offset.setX(0);
			offset.setY(0);
			offset.setZ(-0.02);
			
			this.m_AgStkObjectRootClass.rewind();
			this.m_AgStkObjectRootClass.executeCommand("VO * View FromTo FromRegName \"STK Object\" FromName \"Satellite/"+satName+"\" ToRegName \"STK Object\" ToName \"Satellite/"+satName+"\"");
		}
		finally
		{
			this.m_AgStkObjectRootClass.endUpdate();
			this.m_AgStkObjectRootClass.rewind();
		}
	}
	
	/*package*/ SampleData getSampleData()
	throws AgCoreException
	{
		SampleData data = new SampleData();

		//=========================================
		// Get the current scenario we just loaded.
		//=========================================
		AgScenarioClass scen = null;
		scen = (AgScenarioClass)this.m_AgStkObjectRootClass.getCurrentScenario();

		//=================================================================
		// Get the animation time step from the scenario we just loaded.
		//=================================================================
		IAgScAnimation scanim = scen.getAnimation();
		data.TimeStep = scanim.getAnimStepValue();

		//=================================================================
		// By default we know the start and stop time is in data format UTCG
		// so we get the String value from the Variant. If you change the
		// default unit settings for the time, you may have to change this code
		// to something other than getString(). If you don't you will probably
		// receieve and exception here stating the variant is not a String type.
		//=================================================================
		String startTime = (String)scen.getStartTime_AsObject();
		data.StartTime = startTime;

		String stopTime = (String)scen.getStopTime_AsObject();
		data.StopTime = stopTime;

		IAgStkObjectCollection scenChildren = scen.getChildren();
		int childCount = scenChildren.getCount();

		for(int i = 0; i < childCount; i++)
		{
			//first satellite found
			IAgStkObject obj = scenChildren.getItem(new Integer(i));
			if(obj.getClassType_AsObject().equals(AgESTKObjectType.E_SATELLITE))
			{
				data.SatelliteName = obj.getInstanceName();

				//first sensor found
				IAgStkObject obj2 = obj.getChildren().getItem(new Integer(i));
				if(obj2.getClassType_AsObject().equals(AgESTKObjectType.E_SENSOR))
				{
					data.SensorName = obj2.getInstanceName();
					break;
				}
			}
		}

		return data;
	}
	
	/*package*/ void compute(SampleData data)
	throws Throwable
	{
		this.m_AgStkObjectRootClass.executeCommand("VO */Satellite/" + data.SatelliteName + "/Sensor/" + data.SensorName + " Obscuration Object On Satellite/" + data.SatelliteName);			
		this.m_AgStkObjectRootClass.executeCommand("VO */Satellite/" + data.SatelliteName + "/Sensor/" + data.SensorName + " Obscuration Compute \""+data.StartTime+"\" \""+data.StopTime+"\" "+300.0+" " + "\"" + data.ReportName + "\"");
	}
}