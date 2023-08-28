//AGI Java API
import agi.core.*;
import agi.stkutil.*;
import agi.stkvgt.IAgCrdnEventIntervalSmartInterval;
import agi.stkobjects.*;

public class SampleCode
{
	private AgStkObjectRootClass	m_AgStkObjectRootClass;

	private boolean					m_bFirstTime;

	/* package */SampleCode(AgStkObjectRootClass root)
	throws AgCoreException
	{
		this.m_AgStkObjectRootClass = root;
		this.m_bFirstTime = true;
	}

	/*package*/ static String getReportName(String satName, String reportType)
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
		sb.append(reportType);
		//sb.append("_");
		//sb.append(System.currentTimeMillis());
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
			IAgSatellite sat = null;
			sat = (IAgSatellite)scenChildren._new(AgESTKObjectType.E_SATELLITE, satName);
			
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
			//elijah's model
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
			// Input to a classical orbit state
			// ====================================
			IAgVeInitialState initState = twobody.getInitialState();
			IAgOrbitState os = initState.getRepresentation();
			os.setEpoch(scen.getStartTime());
			os.assignClassical(AgECoordinateSystem.E_COORDINATE_SYSTEM_J2000, 6878.14, 0.0, 45.0, 0.0, 0.0, 0.0);

			// ===================================================================
			// Now propagate the twobody classical J2000 coordinate system orbit
			// ===================================================================
			twobody.propagate();

			this.m_AgStkObjectRootClass.rewind();
			this.m_AgStkObjectRootClass.executeCommand("VO * View FromTo FromRegName \"STK Object\" FromName \"Satellite/"+satName+"\" ToRegName \"STK Object\" ToName \"Satellite/"+satName+"\"");
		}
		finally
		{
			this.m_AgStkObjectRootClass.endUpdate();
			this.m_AgStkObjectRootClass.rewind();
		}
	}
	
	/*package*/ SampleData getSampleData(int radius)
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
        //data.TimeStep = 6.0;
		//=================================================================
		// By default we know the start and stop time is in data format UTCG
		// so we get the String value from the Variant. If you change the
		// default unit settings for the time, you may have to change this code
		// to something other than getString(). If you don't you will probably
		// receieve and exception here stating the variant is not a String type.
		//=================================================================
		String startTime = (String)scen.getStartTime_AsObject();
		data.StartTime = startTime;
        //data.StartTime = "21 Apr 2019 19:00:00.000";
		String stopTime = (String)scen.getStopTime_AsObject();
		data.StopTime = stopTime;
        //data.StopTime = "22 Apr 2019 19:00:00.000";
		data.ReportTime = startTime;
		
		IAgStkObjectCollection scenChildren = scen.getChildren();
		int childCount = scenChildren.getCount();

		for(int i = 0; i < childCount; i++)
		{
			IAgStkObject obj = scenChildren.getItem(new Integer(i));
			if(obj.getClassType_AsObject().equals(AgESTKObjectType.E_SATELLITE))
			{
				data.SatelliteName = obj.getInstanceName();
				break;
			}
		}

		data.Radius = radius;
		data.ReportType = "Power";

		return data;
	}
	
	/*package*/ void compute(SampleData data)
	throws Throwable
	{
		if(this.m_bFirstTime)
		{
			this.m_AgStkObjectRootClass.executeCommand("VO */Satellite/" + data.SatelliteName + " SolarPanel Visualization AddGroup default");
			this.m_bFirstTime = false;
		}
		else
		{
			this.m_AgStkObjectRootClass.executeCommand("VO */Satellite/" + data.SatelliteName + " SolarPanel DeleteData");
		}

		this.m_AgStkObjectRootClass.executeCommand("VO */Satellite/" + data.SatelliteName + " SolarPanel Visualization Radius On " + data.Radius);

		StringBuffer sb = new StringBuffer();
		sb.append("VO */Satellite/" + data.SatelliteName + " SolarPanel Compute ");
		sb.append("\"" + data.StartTime + "\" \"" + data.StopTime + "\" " + 300.0);
		sb.append(" " + data.ReportType + " \"" + data.ReportName + "\"");

//		if(data.ReportType.equalsIgnoreCase("Angles"))
//		{
//			if(data.ReportTime != null || data.ReportTime != "")
//			{
//				sb.append(" \"" + data.ReportTime + "\"");
//			}
//			else
//			{
//				throw new Exception("ReportTime cannot be null");
//			}
//		}

		this.m_AgStkObjectRootClass.executeCommand(sb.toString());
	}
	
	/*package*/ void clearComputation(SampleData data)
	throws AgCoreException
	{
		if(this.m_bFirstTime == false)
		{
			this.m_bFirstTime = true;
			String name = data.SatelliteName;
			if(name != null)
			{
				if(name != "")
				{
					this.m_AgStkObjectRootClass.executeCommand("VO */Satellite/" + name + " SolarPanel DeleteData");
				}
			}
		}
	}
}