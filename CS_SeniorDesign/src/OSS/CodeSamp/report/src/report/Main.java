package report;
import java.util.logging.*;
import java.awt.*;
import java.awt.event.*;

import javax.swing.*;
import javax.swing.plaf.metal.*;

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
public class Main {
	
	    public static void main(String[] args) {
	        SwingUtilities.invokeLater(new Runnable() {
	            @Override
	            public void run() {
	                new Calculator().setVisible(true);
	            }
	        });
	    }
	

}
