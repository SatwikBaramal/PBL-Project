import java.io.IOException;
import java.util.List;
import java.util.concurrent.ExecutionException;

public class Main {
    public static void main(String[] args) throws Exception {
        // Hardcoded file paths
        String dictionaryFilePath = "C:/Users/mbara/Desktop/Codes/PBL-Project/Attempt2/words.txt";
        String textFilePath = "C:/Users/mbara/Desktop/Codes/PBL-Project/Attempt2/input.txt";

        try {
            Dictionary dictionary = new Dictionary(dictionaryFilePath);
            List<String> words = TextFileHandler.readWordsFromFile(textFilePath);

            SpellChecker spellChecker = new SpellChecker(dictionary, 4);
            spellChecker.checkSpelling(words);
        } catch (IOException | InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }
    }
}
