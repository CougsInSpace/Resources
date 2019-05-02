/* ==============================================================
 * This sample was last tested with the following configuration:
 * ==============================================================
 * Eclipse SDK Version: 4.2.0 Build id: I20120608-1400
 * JRE 1.4.2_10 and greater
 * STK 10.0
 * ==============================================================
 */

// Java API
import javax.swing.*;
import javax.swing.plaf.metal.*;

// AGI Java API
import agi.swing.plaf.metal.*;
import agi.core.*;

public class Main
{
	public static void main(String[] args)
	{
		try
		{
			AgCore_JNI.xInitThreads();
			
			MetalLookAndFeel.setCurrentTheme(AgMetalThemeFactory.getDefaultMetalTheme());
			UIManager.setLookAndFeel(MetalLookAndFeel.class.getName());
			JFrame.setDefaultLookAndFeelDecorated(true);
			
			Runnable r = new Runnable()
			{
				public void run()
				{
					try
					{
						MainWindow mw = new MainWindow();
						mw.setVisible(true);
						mw.setLocationRelativeTo(null);
					}
					catch(AgCoreException ce)
					{
						ce.printHexHresult();
						ce.printStackTrace();
					}
					catch(Throwable t)
					{
						t.printStackTrace();
					}
				}
			};
			SwingUtilities.invokeLater(r);
		}
		catch(Throwable t)
		{
			t.printStackTrace();
		}
	}
}