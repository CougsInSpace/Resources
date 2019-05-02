import java.awt.*;
import java.awt.event.*;

import javax.swing.*;
import javax.swing.border.*;

public class SampleJPanel
extends JPanel
implements ItemListener
{
	private static final long	serialVersionUID	= 1L;

	public final static String	s_STEP1_CREATESCENARIO_TEXT	= "1. Create Scenario";
	public final static String	s_STEP2_COMPUTE_TEXT		= "2. Compute";
	public final static String	s_STEP3_CLOSESCENARIO_TEXT	= "3. Close Scenario";

	private JButton				m_stepOneButton;
	private JButton				m_stepTwoButton;
	private JButton				m_stepThreeButton;

	private JLabel				m_StartTimeJLabel;
	private JTextField			m_StartTimeJTextField;

	private JLabel				m_StopTimeJLabel;
	private JTextField			m_StopTimeJTextField;

	private JLabel				m_TimeStepJLabel;
	private JTextField			m_TimeStepJTextField;

	private JLabel				m_SatelliteJLabel;
	private JTextField			m_SatelliteJTextField;

	private JLabel				m_RadiusJLabel;
	private JTextField			m_RadiusJTextField;

	private JLabel				m_ReportTypeJLabel;
	private JComboBox			m_ReportTypeJComboBox;

	private JLabel				m_ReportTimeJLabel;
	private JTextField			m_ReportTimeJTextField;

	public SampleJPanel()
	{
		this.setLayout(new GridLayout(17, 1));

		this.m_stepOneButton = new JButton(s_STEP1_CREATESCENARIO_TEXT);
		this.m_stepOneButton.setAlignmentX(LEFT_ALIGNMENT);
		this.m_stepOneButton.setHorizontalAlignment(SwingConstants.LEFT);
		this.add(this.m_stepOneButton);

		this.m_StartTimeJLabel = new JLabel();
		this.m_StartTimeJLabel.setBorder(new EmptyBorder(0, 10, 0, 10));
		this.m_StartTimeJLabel.setText(" Start Time: ");
		this.add(this.m_StartTimeJLabel);

		this.m_StartTimeJTextField = new JTextField();
		this.m_StartTimeJTextField.setBorder(new EmptyBorder(0, 10, 0, 10));
		this.add(this.m_StartTimeJTextField);

		this.m_StopTimeJLabel = new JLabel();
		this.m_StopTimeJLabel.setBorder(new EmptyBorder(0, 10, 0, 10));
		this.m_StopTimeJLabel.setText(" Stop Time: ");
		this.add(this.m_StopTimeJLabel);

		this.m_StopTimeJTextField = new JTextField();
		this.m_StopTimeJTextField.setBorder(new EmptyBorder(0, 10, 0, 10));
		this.add(this.m_StopTimeJTextField);

		this.m_TimeStepJLabel = new JLabel();
		this.m_TimeStepJLabel.setBorder(new EmptyBorder(0, 10, 0, 10));
		this.m_TimeStepJLabel.setText(" Time Step: ");
		this.add(this.m_TimeStepJLabel);

		this.m_TimeStepJTextField = new JTextField();
		this.m_TimeStepJTextField.setBorder(new EmptyBorder(0, 10, 0, 10));
		this.add(this.m_TimeStepJTextField);

		this.m_SatelliteJLabel = new JLabel();
		this.m_SatelliteJLabel.setBorder(new EmptyBorder(0, 10, 0, 10));
		this.m_SatelliteJLabel.setText(" Satellite: ");
		this.add(this.m_SatelliteJLabel);

		this.m_SatelliteJTextField = new JTextField();
		this.m_SatelliteJTextField.setBorder(new EmptyBorder(0, 10, 0, 10));
		this.m_SatelliteJTextField.setEditable(false);
		this.m_SatelliteJTextField.setEnabled(false);
		this.add(this.m_SatelliteJTextField);

		this.m_RadiusJLabel = new JLabel();
		this.m_RadiusJLabel.setBorder(new EmptyBorder(0, 10, 0, 10));
		this.m_RadiusJLabel.setText(" Radius: ");
		this.add(this.m_RadiusJLabel);

		this.m_RadiusJTextField = new JTextField();
		this.m_RadiusJTextField.setBorder(new EmptyBorder(0, 10, 0, 10));
		this.add(this.m_RadiusJTextField);

		this.m_ReportTypeJLabel = new JLabel();
		this.m_ReportTypeJLabel.setBorder(new EmptyBorder(0, 10, 0, 10));
		this.m_ReportTypeJLabel.setText(" Report Type: ");
		this.add(this.m_ReportTypeJLabel);

		this.m_ReportTypeJComboBox = new JComboBox();
		this.m_ReportTypeJComboBox.setBorder(new EmptyBorder(0, 10, 0, 10));
		this.m_ReportTypeJComboBox.addItem("Power");
		this.m_ReportTypeJComboBox.addItem("Area");
		//this.m_ReportTypeJComboBox.addItem("Angles");
		this.m_ReportTypeJComboBox.addItemListener(this);
		this.add(this.m_ReportTypeJComboBox);

		this.m_ReportTimeJLabel = new JLabel();
		this.m_ReportTimeJLabel.setBorder(new EmptyBorder(0, 10, 0, 10));
		this.m_ReportTimeJLabel.setText(" Report Time: ");
		this.add(this.m_ReportTimeJLabel);

		this.m_ReportTimeJTextField = new JTextField();
		this.m_ReportTimeJTextField.setBorder(new EmptyBorder(0, 10, 0, 10));
		this.m_ReportTimeJTextField.setEnabled(false);
		this.m_ReportTimeJTextField.setEditable(false);
		this.add(this.m_ReportTimeJTextField);

		this.m_stepTwoButton = new JButton(s_STEP2_COMPUTE_TEXT);
		this.m_stepTwoButton.setAlignmentX(LEFT_ALIGNMENT);
		this.m_stepTwoButton.setHorizontalAlignment(SwingConstants.LEFT);
		this.add(this.m_stepTwoButton);

		this.m_stepThreeButton = new JButton(s_STEP3_CLOSESCENARIO_TEXT);
		this.m_stepThreeButton.setAlignmentX(LEFT_ALIGNMENT);
		this.m_stepThreeButton.setHorizontalAlignment(SwingConstants.LEFT);
		this.add(this.m_stepThreeButton);
	}

	public void addActionListener(ActionListener al)
	{
		this.getStepOne().addActionListener(al);
		this.getStepTwo().addActionListener(al);
		this.getStepThree().addActionListener(al);
	}

	public JButton getStepOne()
	{
		return this.m_stepOneButton;
	}

	public JButton getStepTwo()
	{
		return this.m_stepTwoButton;
	}

	public JButton getStepThree()
	{
		return this.m_stepThreeButton;
	}

	public String getStartTime()
	{
		return this.m_StartTimeJTextField.getText();
	}

	public void setStartTime(String time)
	{
		this.m_StartTimeJTextField.setText(time);
	}

	public String getStopTime()
	{
		return this.m_StopTimeJTextField.getText();
	}

	public void setStopTime(String time)
	{
		this.m_StopTimeJTextField.setText(time);
	}

	public double getTimeStep()
	{
		return Double.parseDouble(this.m_TimeStepJTextField.getText());
	}

	public void setTimeStep(double step)
	{
		this.m_TimeStepJTextField.setText(new Double(step).toString());
	}

	public String getSatName()
	{
		return this.m_SatelliteJTextField.getText();
	}

	public void setSatName(String name)
	{
		this.m_SatelliteJTextField.setText(name);
	}

	public int getRadius()
	{
		return Integer.parseInt(this.m_RadiusJTextField.getText());
	}

	public void setRadius(int radius)
	{
		this.m_RadiusJTextField.setText(new Integer(radius).toString());
	}

	public String getReportType()
	{
		return (String)this.m_ReportTypeJComboBox.getSelectedItem();
	}

	public void setReportType(String type)
	{
		this.m_ReportTypeJComboBox.setSelectedItem(type);
	}

	public String getReportTime()
	{
		return this.m_ReportTimeJTextField.getText();
	}

	public void setReportTime(String time)
	{
		this.m_ReportTimeJTextField.setText(time);
	}

	public void itemStateChanged(ItemEvent ie)
	{
		String item = (String)ie.getItem();

		if(item == "Angles")
		{
			this.m_ReportTimeJTextField.setEnabled(true);
		}
		else
		{
			this.m_ReportTimeJTextField.setEnabled(false);
		}
	}

	public SampleData getData()
	{
		SampleData data = new SampleData();

		data.StartTime = this.getStartTime();
		data.StopTime = this.getStopTime();
		data.TimeStep = this.getTimeStep();

		data.SatelliteName = this.getSatName();

		data.Radius = this.getRadius();

		data.ReportType = this.getReportType();
		data.ReportTime = this.getReportTime();

		data.ReportName = SampleCode.getReportName(data.SatelliteName, data.ReportType);

		return data;
	}

	public void setData(SampleData data)
	{
		if(data != null)
		{
			this.setStartTime(data.StartTime);
			this.setStopTime(data.StopTime);
			this.setTimeStep(data.TimeStep);

			this.setSatName(data.SatelliteName);

			this.setRadius(data.Radius);

			this.setReportType(data.ReportType);
			this.setReportTime(data.ReportTime);
		}
		else
		{
			// clear widgets
		}
	}
}