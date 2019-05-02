package report;
import java.util.logging.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;

import javax.swing.*;
import javax.swing.plaf.metal.*;
import javax.swing.table.AbstractTableModel;


// AGI Java API
import agi.core.logging.*;
import agi.swing.*;
import agi.swing.plaf.metal.*;
import agi.core.*;
import agi.core.awt.*;
import agi.stkx.*;
import agi.stkx.awt.*;
import agi.stkobjects.*;
import agi.stk.core.swing.toolbars.animation.*;
import agi.stkengine.*;
import agi.stkgraphics.IAgStkGraphicsScene;
import agi.stkgraphics.IAgStkGraphicsSceneManager;
//CodeSample helper code
//import agi.customapplications.swing.*;
//import java.awt.event.ActionListener;

//import agi.customapplications.swing.CustomApplicationSTKSampleBaseJFrame;
//import agi.stk.core.swing.toolbars.animation.IAgAnimationJToolBarEventsListener;

public class Calculator 

	extends JFrame
	//implements ActionListener, IAgAnimationJToolBarEventsListener
	{
	private static void showErrorDialog(Exception e) {
	    e.printStackTrace();

	    StringWriter sw = new StringWriter();
	    e.printStackTrace(new PrintWriter(sw));

	    JTextArea textArea = new JTextArea(sw.toString());
	    JScrollPane scrollPane = new JScrollPane(textArea);
	    scrollPane.setPreferredSize(new Dimension(700, 300));
	    textArea.setEditable(false);
	    JOptionPane.showMessageDialog(null, scrollPane, "Unhandled Exception", JOptionPane.ERROR_MESSAGE);

	}


	private static class ViewingOpportunity {
	    public JulianDate StartDate;
	    public JulianDate EndDate;
	    public double ApproachAzimuth;
	    public double DepartureAzimuth;
	}

	private static class ViewingOpportunitiesTableModel extends AbstractTableModel {
	    private static final long serialVersionUID = 1L;

	    private List<ViewingOpportunity> viewingOpportunities = new ArrayList<ViewingOpportunity>();

	    private static final String[] labels = new String[] {
	            "Start Time (UTC)",
	            "Entry Azimuth",
	            "Exit Time (UTC)",
	            "Departure Azimuth"
	    };

	    @Override
	    public int getColumnCount() {
	        return labels.length;
	    }

	    @Override
	    public String getColumnName(int column) {
	        return labels[column];
	    }

	    @Override
	    public int getRowCount() {
	        return viewingOpportunities.size();
	    }

	    @Override
	    public Object getValueAt(int rowIndex, int columnIndex) {
	        switch (columnIndex) {
	        case 0:
	            return viewingOpportunities.get(rowIndex).StartDate.toGregorianDate().toString();
	        case 1:
	            return viewingOpportunities.get(rowIndex).ApproachAzimuth;
	        case 2:
	            return viewingOpportunities.get(rowIndex).EndDate.toGregorianDate().toString();
	        case 3:
	            return viewingOpportunities.get(rowIndex).DepartureAzimuth;
	        default:
	            return null;
	        }
	    }

	    public void setViewingOpportunities(List<ViewingOpportunity> viewingOpportunities) {
	        this.viewingOpportunities = viewingOpportunities;
	        fireTableDataChanged();
	    }
	}


	
	private JTextField startDateBox;
	private JTextField stopDateBox;
	private JTextField latitudeBox;
	private JTextField longitudeBox;
	private JTextField elevationBox;
	private JTextArea tleBox;
	private JButton goButton;
	private JTabbedPane resultsPane;
	private ViewingOpportunitiesTableModel tableModel;
	private JTable table;

	public void onAnimationJToolBarAction(AgAnimationJToolBarEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	public void actionPerformed(ActionEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	public Calculator() {
	    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	    setTitle("Satellite Visibility Calculator");
	    Container contentPane = getContentPane();

	    contentPane.setLayout(new GridBagLayout());

	    Insets defaultInsets = new Insets(5, 5, 5, 5);

	    GridBagConstraints labelConstraints = new GridBagConstraints();
	    labelConstraints.insets = defaultInsets;
	    labelConstraints.gridx = 0;
	    labelConstraints.anchor = GridBagConstraints.LINE_END;

	    GridBagConstraints controlConstraints = new GridBagConstraints();
	    controlConstraints.insets = defaultInsets;
	    controlConstraints.gridx = 1;
	    controlConstraints.anchor = GridBagConstraints.LINE_START;

	    contentPane.add(new JLabel("Start Date (UTC)"), labelConstraints);
	    startDateBox = new JTextField(20);
	    contentPane.add(startDateBox, controlConstraints);

	    contentPane.add(new JLabel("Stop Date (UTC)"), labelConstraints);
	    stopDateBox = new JTextField(20);
	    contentPane.add(stopDateBox, controlConstraints);

	    contentPane.add(new JLabel("Latitude (degrees)"), labelConstraints);
	    latitudeBox = new JTextField(20);
	    contentPane.add(latitudeBox, controlConstraints);

	    contentPane.add(new JLabel("Longitude (degrees)"), labelConstraints);
	    longitudeBox = new JTextField(20);
	    contentPane.add(longitudeBox, controlConstraints);

	    contentPane.add(new JLabel("Min. Elevation Angle (degrees)"), labelConstraints);
	    elevationBox = new JTextField(20);
	    contentPane.add(elevationBox, controlConstraints);

	    contentPane.add(new JLabel("Two-Line Elements (TLE)"), labelConstraints);

	    tleBox = new JTextArea(3, 40);
	    JScrollPane tleBoxScrollPane = new JScrollPane(tleBox);
	    contentPane.add(tleBoxScrollPane, controlConstraints);

	    GridBagConstraints buttonContraints = new GridBagConstraints();
	    buttonContraints.anchor = GridBagConstraints.LINE_END;
	    buttonContraints.insets = defaultInsets;
	    buttonContraints.gridx = 0;
	    buttonContraints.gridwidth = GridBagConstraints.REMAINDER;

	    goButton = new JButton("Go");
	    contentPane.add(goButton, buttonContraints);

	    resultsPane = new JTabbedPane();
	    resultsPane.setPreferredSize(new Dimension(575, 350));

	    Insight3D insight = new Insight3D();
	    resultsPane.addTab("Visualization", insight);

	    tableModel = new ViewingOpportunitiesTableModel();
	    table = new JTable(tableModel);

	    JScrollPane scrollPane = new JScrollPane(table);
	    table.setFillsViewportHeight(true);
	    resultsPane.addTab("Data", scrollPane);

	    GridBagConstraints resultsConstraints = new GridBagConstraints();
	    resultsConstraints.fill = GridBagConstraints.BOTH;
	    resultsConstraints.insets = defaultInsets;
	    resultsConstraints.gridx = 0;
	    resultsConstraints.weightx = 0.5;
	    resultsConstraints.weighty = 0.5;
	    resultsConstraints.gridwidth = GridBagConstraints.REMAINDER;

	    contentPane.add(resultsPane, resultsConstraints);

	    goButton.addActionListener(new ActionListener() {
	        @Override
	        public void actionPerformed(ActionEvent e) {
	            try {
	                performCalculation();
	            } catch (Exception ex) {
	                showErrorDialog(ex);
	            }
	        }
	    });

	    try {
	        setupVisualization();
	    } catch (Exception ex) {
	        showErrorDialog(ex);
	    }

	    pack();
	}


}
