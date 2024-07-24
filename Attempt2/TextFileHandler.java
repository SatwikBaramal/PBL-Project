import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class TextFileHandler {
    public static List<String> readWordsFromFile(String filePath) throws IOException {
        List<String> words = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] splitWords = line.split("\\W+");
                for (String word : splitWords) {
                    if (!word.isEmpty()) {
                        words.add(word);
                    }
                }
            }
        }
        System.out.println("Read " + words.size() + " words from the text file.");
        return words;
    }
}
    


