import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashSet;
import java.util.Set;

public class Dictionary {
    private Set<String> words;

    public Dictionary(String filePath) throws IOException {
        words = new HashSet<>();
        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String word;
            while ((word = br.readLine()) != null) {
                words.add(word.trim().toLowerCase());
            }
        }
        System.out.println("Loaded " + words.size() + " words into the dictionary.");
    }

    public boolean contains(String word) {
        return words.contains(word.toLowerCase());
    }

    public Set<String> getWords() {
        return words;
    }
}