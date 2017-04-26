package org.elsys.serializer.main;

import java.util.Arrays;

import org.elsys.serializer.Serializer;
import org.elsys.serializer.json.JsonSerializer;

public class Main {

	public static void main(String[] args) {
		Student student = new Student();
		student.setName("Pesho");
		student.setFatherName("Ivanov");
		student.setLastName("Peshev");
		student.setGrades(Arrays.asList(2, 5, 6));

		Serializer serializer = new JsonSerializer();
		serializer.setPretty(true);
		String result = serializer.serialize(student);
		serializer.includeNullFields(false);
		System.out.println(result);
	}

}
