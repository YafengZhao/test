import java.util.Iterator;
import java.util.ServiceLoader;
import hello.spi.DemoService;

public class Main {

	public static void main(String[] args) {

		ServiceLoader<DemoService> serviceLoader = 
			ServiceLoader.load(DemoService.class);

		Iterator<DemoService> it = serviceLoader.iterator();

		while(it != null && it.hasNext()) {
			
			DemoService demo = it.next();

			if (demo.getType() == "chinese")
				System.out.println("class: " + demo.getClass().getName() + 
					" **** " + demo.sayHi("World"));
		}
	}
}

