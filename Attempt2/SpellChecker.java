import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class SpellChecker {
    private Dictionary dictionary;
    private ExecutorService executor;
    private static final int MAX_SUGGESTION_DISTANCE = 3;

    public SpellChecker(Dictionary dictionary, int numberOfThreads) {
        this.dictionary = dictionary;
        this.executor = Executors.newFixedThreadPool(numberOfThreads);
    }

    public void checkSpelling(List<String> words) throws InterruptedException, ExecutionException {
        List<Future<Void>> futures = new ArrayList<>();
        for (String word : words) {
            futures.add(executor.submit(new SpellCheckTask(word)));
        }

        for (Future<Void> future : futures) {
            future.get();
        }

        executor.shutdown();
    }

    private class SpellCheckTask implements Callable<Void> {
        private String word;

        SpellCheckTask(String word) {
            this.word = word;
        }

        @Override
        public Void call() {
            System.out.println("Checking word: " + word);
            // Convert word to lowercase and strip punctuation before checking
            String processedWord = word.toLowerCase().replaceAll("[^a-z]", "");
            if (!dictionary.contains(processedWord)) {
                suggestCorrections(word, processedWord);
            }
            return null;
        }

        private void suggestCorrections(String originalWord, String processedWord) {
            System.out.println("Suggesting corrections for: " + originalWord);
            int minDistance = Integer.MAX_VALUE;
            List<String> bestMatches = new ArrayList<>();
            for (String dictWord : dictionary.getWords()) {
                int distance = WagnerFischer.computeLevenshteinDistance(processedWord, dictWord);
                if (distance < minDistance && distance <= MAX_SUGGESTION_DISTANCE) {
                    minDistance = distance;
                    bestMatches.clear();
                    bestMatches.add(dictWord);
                } else if (distance == minDistance)
                    bestMatches.add(dictWord);
            }
            if (!bestMatches.isEmpty()) {
                System.out.println("Misspelled word: " + originalWord + ", Suggestions: " + bestMatches);
            } else {
                System.out.println("Misspelled word: " + originalWord + ", No suitable suggestions found.");
            }
        }
    }
}
