/** Generated by YAKINDU Statechart Tools code generator. */
package traffic.light;

import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import org.yakindu.sct.IStatemachine;
import org.yakindu.sct.ITimerCallback;
import org.yakindu.sct.rx.Observable;

public interface ITrafficLightCtrl extends ITimerCallback,IStatemachine {
	
	public interface Interface {
	
		public void raisePolice_interrupt();
		
		public void raiseToggle();
		
		public long getRedPeriod();
		
		public void setRedPeriod(long value);
		
		public long getGreenPeriod();
		
		public void setGreenPeriod(long value);
		
		public long getYellowPeriod();
		
		public void setYellowPeriod(long value);
		
	}
	
	public Interface getInterface();
	
	
	public interface InterfaceTrafficLight {
	
		public Observable<Void> getDisplayRed();
		
		public Observable<Void> getDisplayGreen();
		
		public Observable<Void> getDisplayYellow();
		
		public Observable<Void> getDisplayNone();
		
		public List<InterfaceTrafficLightListener> getListeners();
	}
	
	public interface InterfaceTrafficLightListener {
	
		public void onDisplayRedRaised();
		public void onDisplayGreenRaised();
		public void onDisplayYellowRaised();
		public void onDisplayNoneRaised();
	}
	
	public InterfaceTrafficLight getInterfaceTrafficLight();
	
	
	public interface InterfaceTimer {
	
		public static final long oFF = -1;
		
		public Observable<String> getUpdateTimerColour();
		
		public Observable<Long> getUpdateTimerValue();
		
		public long getOFF();
		
		public List<InterfaceTimerListener> getListeners();
	}
	
	public interface InterfaceTimerListener {
	
		public void onUpdateTimerColourRaised(String value);
		public void onUpdateTimerValueRaised(long value);
	}
	
	public InterfaceTimer getInterfaceTimer();
	
}
