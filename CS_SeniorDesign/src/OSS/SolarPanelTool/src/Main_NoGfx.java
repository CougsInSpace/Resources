import java.io.BufferedReader;
import java.io.FileReader;

import agi.core.awt.AgAwt_JNI;
import agi.stkengine.AgStkCustomApplication_JNI;
import agi.stkobjects.AgStkObjectRootClass;
import agi.stkx.AgEFeatureCodes;
import agi.stkx.AgSTKXApplicationClass;

public class Main_NoGfx {
	private SampleCode				m_SampleCode;
	private AgSTKXApplicationClass	m_AgSTKXApplicationClass;
	private AgStkObjectRootClass	m_AgStkObjectRootClass;
	public Main_NoGfx() throws Throwable {
		
		AgAwt_JNI.initialize_AwtDelegate();
		AgStkCustomApplication_JNI.initialize(true); // true parameter allows for smart auto class cast
		AgAwt_JNI.initialize_AwtComponents();
		
		this.m_AgSTKXApplicationClass = new AgSTKXApplicationClass();
		m_AgSTKXApplicationClass.setNoGraphics(true);
		if(!this.m_AgSTKXApplicationClass.isFeatureAvailable(AgEFeatureCodes.E_FEATURE_CODE_ENGINE_RUNTIME))
		{
			String msg = "STK Engine Runtime license is required to run this sample.  Exiting!";
			System.out.println(msg);
			System.exit(0);
		}
		
		this.m_AgStkObjectRootClass = new AgStkObjectRootClass();
		this.m_SampleCode = new SampleCode(this.m_AgStkObjectRootClass);
		this.m_SampleCode.createScenario();
		SampleData data = this.m_SampleCode.getSampleData(10);
		this.m_SampleCode.compute(data);
		this.loadReport(data.ReportName);
		this.m_AgStkObjectRootClass.closeScenario();
	}
	
	private void loadReport(String reportName) throws Throwable
		{

			FileReader fr = new FileReader(reportName);
			BufferedReader br = new BufferedReader(fr);

			String reportData = br.readLine();

			while(reportData != null)
			{
				reportData = br.readLine();
			}

			br.close();
			br = null;
		}
}
