// Java API
import java.util.logging.*;
import java.io.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.plaf.metal.*;

// AGI Java API
import agi.core.logging.*;
import agi.swing.*;
import agi.swing.msgviewer.*;
import agi.swing.plaf.metal.*;
import agi.swing.toolbars.msgviewer.*;
import agi.core.*;
import agi.core.awt.*;
import agi.stkx.*;
import agi.stkx.awt.*;
import agi.stkobjects.*;
import agi.stkengine.*;

//CodeSample helper code
import agi.customapplications.swing.*;

public class MainWindow
//NOTE:  This sample derives/extends from CustomApplicationSTKSampleBaseJFrame in order to provide
//common sample help regarding Java properties, connect command toolbar, common STK Engine functionality.
//You application is not required to derive from this class or have the same features it provides, but rather
//from the standard JFrame, Frame, or other preference.
extends CustomApplicationSTKSampleBaseJFrame
implements ActionListener, IAgMsgViewerJToolBarEventsListener
{
	private static final long		serialVersionUID	= 1L;
	private final static String		s_TITLE				= "OSS_SolarPanelTool";
	private final static String		s_DESCFILENAME		= "AppDescription.html";

	private AgSTKXApplicationClass	m_AgSTKXApplicationClass;
	private AgStkObjectRootClass	m_AgStkObjectRootClass;

	private AgGfxAnalysisCntrlClass	m_AgGfxAnalysisCntrlClass;
	private AgGlobeCntrlClass		m_AgGlobeCntrlClass;
	private AgMsgViewerJPanel		m_AgMsgViewerJPanel;													;

	private SampleJPanel			m_SampleJPanel;
	private SampleCode				m_SampleCode;

	public MainWindow()
	throws Throwable
	{
		super(MainWindow.class.getResource(s_DESCFILENAME));

		// ================================================
		// Set the logging level to Level.FINEST to get
		// all AGI java console logging
		// ================================================
		ConsoleHandler ch = new ConsoleHandler();
		ch.setLevel(Level.OFF);
		ch.setFormatter(new AgFormatter());
		Logger.getLogger("agi").setLevel(Level.OFF);
		Logger.getLogger("agi").addHandler(ch);

		// =========================================
		// This must be called before all
		// AWT/Swing/StkUtil/Stkx/StkObjects calls
		// =========================================
		AgAwt_JNI.initialize_AwtDelegate();
		AgStkCustomApplication_JNI.initialize(true); // true parameter allows for smart auto class cast
		AgAwt_JNI.initialize_AwtComponents();

		this.getContentPane().setLayout(new BorderLayout());
		this.setTitle(s_TITLE);
		this.setIconImage(new AgAGIImageIcon().getImage());

		this.m_AgSTKXApplicationClass = new AgSTKXApplicationClass();
		this.setApp(this.m_AgSTKXApplicationClass);

		if(!this.m_AgSTKXApplicationClass.isFeatureAvailable(AgEFeatureCodes.E_FEATURE_CODE_ENGINE_RUNTIME))
		{
			String msg = "STK Engine Runtime license is required to run this sample.  Exiting!";
			JOptionPane.showMessageDialog(this, msg, "License Error", JOptionPane.ERROR_MESSAGE);
			System.exit(0);
		}

		if(!this.m_AgSTKXApplicationClass.isFeatureAvailable(AgEFeatureCodes.E_FEATURE_CODE_GLOBE_CONTROL))
		{
			String msg = "You do not have the required STK Globe license.  The sample's globe will not display properly.";
			JOptionPane.showMessageDialog(this, msg, "License Error", JOptionPane.ERROR_MESSAGE);
		}

		this.m_AgStkObjectRootClass = new AgStkObjectRootClass();
		this.setRoot(this.m_AgStkObjectRootClass);

		JPanel cntrlJPanel = new JPanel();
		cntrlJPanel.setLayout(new GridLayout(1, 2));

		MetalTheme mt = AgMetalThemeFactory.getDefaultMetalTheme();
		Color awtColor = mt.getPrimaryControl();
		AgCoreColor stkxColor = AgAwtColorTranslator.fromAWTtoCoreColor(awtColor);

		this.m_AgGlobeCntrlClass = new AgGlobeCntrlClass();
		this.m_AgGlobeCntrlClass.setBackColor(stkxColor);
		this.m_AgGlobeCntrlClass.setBackground(awtColor);
		cntrlJPanel.add(this.m_AgGlobeCntrlClass);
		
		this.m_AgGfxAnalysisCntrlClass = new AgGfxAnalysisCntrlClass();
		this.m_AgGfxAnalysisCntrlClass.setBackColor(stkxColor);
		this.m_AgGfxAnalysisCntrlClass.setBackground(awtColor);
		this.m_AgGfxAnalysisCntrlClass.setControlMode(AgEGfxAnalysisMode.E_SOLAR_PANEL_TOOL);
		cntrlJPanel.add(this.m_AgGfxAnalysisCntrlClass);

		this.m_AgMsgViewerJPanel = new AgMsgViewerJPanel();
		this.m_AgMsgViewerJPanel.getMsgViewerJToolBar().addMsgViewerJToolBarListener(this);

		JSplitPane mainSplitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT, cntrlJPanel, this.m_AgMsgViewerJPanel);
		mainSplitPane.setResizeWeight(0.75);
		this.getContentPane().add(mainSplitPane, BorderLayout.CENTER);

		this.m_SampleJPanel = new SampleJPanel();
		this.m_SampleJPanel.setPreferredSize(new Dimension(200, 618));
		this.m_SampleJPanel.addActionListener(this);
		this.getContentPane().add(this.m_SampleJPanel, BorderLayout.EAST);

		this.m_SampleCode = new SampleCode(this.m_AgStkObjectRootClass);

		// Remove unwanted menu bars for this sample
		JMenu scenarioJMenu = this.getCustomAppSTKSampleBaseJMenuBar().getScenarioJMenu();
		this.getCustomAppSTKSampleBaseJMenuBar().remove(scenarioJMenu);
		JMenu vdfJMenu = this.getCustomAppSTKSampleBaseJMenuBar().getVDFJMenu();
		this.getCustomAppSTKSampleBaseJMenuBar().remove(vdfJMenu);
		JMenu sampleJMenu = this.getCustomAppSTKSampleBaseJMenuBar().getSampleJMenu();
		this.getCustomAppSTKSampleBaseJMenuBar().remove(sampleJMenu);
		this.getCustomAppSTKSampleBaseJMenuBar().invalidate();
		this.getCustomAppSTKSampleBaseJMenuBar().repaint();

		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.addWindowListener(new MainWindowAdapter());

		this.setSize(1000, 618);
	}

	private void loadReport(String reportName)
	throws Throwable
	{
		this.m_AgMsgViewerJPanel.clearMessages();

		FileReader fr = new FileReader(reportName);
		BufferedReader br = new BufferedReader(fr);

		String reportData = br.readLine();

		while(reportData != null)
		{
			this.m_AgMsgViewerJPanel.writeMessage(reportData);

			reportData = br.readLine();
		}

		br.close();
		br = null;
	}

	public void actionPerformed(ActionEvent ae)
	{
		try
		{
			((Component)this).setCursor(new Cursor(Cursor.WAIT_CURSOR));

			if(ae.getActionCommand().equalsIgnoreCase(SampleJPanel.s_STEP1_CREATESCENARIO_TEXT))
			{
				this.m_SampleCode.createScenario();
				SampleData data = this.m_SampleCode.getSampleData(10);
				this.m_SampleJPanel.setData(data);
			}
			else if(ae.getActionCommand().equalsIgnoreCase(SampleJPanel.s_STEP2_COMPUTE_TEXT))
			{
				SampleData data = this.m_SampleJPanel.getData();
				this.m_SampleCode.compute(data);
				this.loadReport(data.ReportName);
			}
			else if(ae.getActionCommand().equalsIgnoreCase(SampleJPanel.s_STEP3_CLOSESCENARIO_TEXT))
			{
				SampleData data = this.m_SampleJPanel.getData();
				this.m_SampleCode.clearComputation(data);
				this.m_SampleJPanel.setData(null);
				this.m_AgStkObjectRootClass.closeScenario();
			}
		}
		catch(Throwable t)
		{
			JOptionPane.showMessageDialog(this, t.getMessage(), "SolarPanelTool Error", JOptionPane.ERROR_MESSAGE, null);
			t.printStackTrace();
		}
		finally
		{
			((Component)this).setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
		}
	}

	public void onMsgViewerJToolBarAction(AgMsgViewerJToolBarEvent e)
	{
		try
		{
			((Component)this).setCursor(new Cursor(Cursor.WAIT_CURSOR));

			int action = e.getMsgViewerJToolBarAction();
			if(action == AgMsgViewerJToolBarEvent.ACTION_MSGVIEWER_SAVEAS)
			{
				this.m_AgMsgViewerJPanel.saveMessages();
			}
			else if(action == AgMsgViewerJToolBarEvent.ACTION_MSGVIEWER_CLEAR)
			{
				this.m_AgMsgViewerJPanel.clearMessages();
			}
		}
		catch(Throwable t)
		{
			t.printStackTrace();
		}
		finally
		{
			((Component)this).setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
		}
	}

	private class MainWindowAdapter
	extends WindowAdapter
	{
		public void windowClosing(WindowEvent evt)
		{
			try
			{
				// Must dispose your control before uninitializing the API
				MainWindow.this.m_AgGfxAnalysisCntrlClass.dispose();
				MainWindow.this.m_AgGlobeCntrlClass.dispose();

				// Reverse of the initialization order
				AgAwt_JNI.uninitialize_AwtComponents();
				AgStkCustomApplication_JNI.uninitialize();
				AgAwt_JNI.uninitialize_AwtDelegate();
			}
			catch(Throwable t)
			{
				t.printStackTrace();
			}
		}
	}
}