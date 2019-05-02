// Java API
import javax.swing.*;
import java.awt.GraphicsEnvironment;
// AGI Java API
import agi.core.*;

public class Main
{	
	public static void main(String[] args)
	{
		try
		{
//			System.setProperty("java.awt.headless", "true");
			AgCore_JNI.xInitThreads();
			
//			if(!GraphicsEnvironment.isHeadless())
//			{
//				System.out.println("Not headless for some reason");
//				return;
//			}
			
			Runnable r = new Runnable() 
			{
				public void run()
				{
					try 
					{
						Access access = new Access();
						access.compute();
					}
					catch(AgCoreException ce)
					{
						ce.printHexHresult();
						ce.printStackTrace();
					}
					catch (Throwable t) 
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