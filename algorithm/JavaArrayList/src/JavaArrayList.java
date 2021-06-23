import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Iterator;

public class JavaArrayList {

	public static void printArray(final ArrayList<String> words) {
		System.out.print('[');
		boolean first = true;
		for (final String word : words) {
			if (first) {
				first = false;
			} else {
				System.out.print(", ");
			}
			System.out.print(word);
		}
		System.out.println(']');
	}
	
	public static void main(String[] args) {
		ArrayList<String> words1 = new ArrayList<>(
				Arrays.asList("the", "frogurt", "is", "also", "cursed")
				);
		printArray(words1);
		
		ArrayList<String> words2 = new ArrayList<>(words1);
		printArray(words2);
		
		ArrayList<String> words3 = new ArrayList<>(Collections.nCopies(5, "Mo"));
		printArray(words3);
		
		System.out.print("\n foreach ArrayList\n");
		for (final String word : words1) {
			System.out.println(": " + word);
		}
		
		System.out.print("\n for-loop ArrayList\n");
		for (Iterator<String> iter = words1.iterator(); iter.hasNext();) {
			System.out.println(": " + iter.next());
		}
		
		System.out.print("\n ArrayList.get(0)\n");
		System.out.println(words1.get(0));
		
		System.out.print("\n add(index, str)\n");
		words1.add(0, "First");
		printArray(words1);
		
		words1.add(1, "appended");
		printArray(words1);
		
		System.out.print("\n add(str) to last element\n");
		words1.add("last");
		printArray(words1);
		
		System.out.print("\n remove()\n");
		words1.remove(0);
		printArray(words1);
		
		words1.subList(1, 3).clear();
		printArray(words1);
		
		System.out.print("\n swap()\n");
		Collections.swap(words1, 0, 1);
		printArray(words1);
		Collections.swap(words1, 0, 1);
		printArray(words1);
		
		System.out.print("\n indexOf()\n");
		System.out.println("index: " + words1.indexOf("also"));
	}

}
