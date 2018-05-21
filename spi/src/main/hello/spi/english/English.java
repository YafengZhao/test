package hello.spi.english;

import hello.spi.DemoService;

public class English implements DemoService {

	final String type = "english";
	public English() {

		System.out.println("========English Constructor=========");
	}

	public String getType() {

		return type;
	}

	public String sayHi(String msg) {

		return "Hello" + msg;
	}
}
