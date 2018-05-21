package hello.spi.chinese;

import hello.spi.DemoService;

public class Chinese implements DemoService {

	final String type = "chinese";
	public Chinese() {
		
		System.out.println("=====Chinese Constructor=======");
	}

	public String getType() {

		return type;
	}

	public String sayHi(String msg) {

		return "NiHao" + msg;
	}
}
