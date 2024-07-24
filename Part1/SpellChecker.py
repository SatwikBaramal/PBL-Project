import tkinter as tk
from tkinter import scrolledtext, messagebox

class SpellCheckerGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Spell Checker")
        self.root.geometry("600x500")
        self.root.configure(bg='#2e2e2e')

        self.dictionary = self.load_dictionary("PBL-Project\words.txt")

        self.create_widgets()

    def create_widgets(self):
        # Title Label
        title_label = tk.Label(self.root, text="Spell Checker", bg='#2e2e2e', fg='white', font=('Helvetica', 24, 'bold'))
        title_label.pack(pady=20)

        # Frame for input area and button
        input_frame = tk.Frame(self.root, bg='#2e2e2e')
        input_frame.pack(padx=20, pady=10, fill=tk.X)

        # Input Text Area
        self.input_text_area = scrolledtext.ScrolledText(input_frame, wrap=tk.WORD, width=60, height=7, bg='#404040', fg='white', insertbackground='white', font=('Helvetica', 12))
        self.input_text_area.pack(padx=10, pady=5)

        # Check Spelling Button
        self.check_button = tk.Button(input_frame, text="Check Spelling", command=self.check_spelling, bg='#007acc', fg='white', activebackground='#005f99', activeforeground='white', font=('Helvetica', 14, 'bold'))
        self.check_button.pack(pady=10)

        # Output Label
        output_label = tk.Label(self.root, text="Suggestions:", bg='#2e2e2e', fg='white', font=('Helvetica', 18, 'bold'))
        output_label.pack(pady=10)

        # Output Text Area
        self.output_text_area = scrolledtext.ScrolledText(self.root, wrap=tk.WORD, width=60, height=10, bg='#404040', fg='white', state='disabled', font=('Helvetica', 12))
        self.output_text_area.pack(padx=20, pady=10)

    def load_dictionary(self, file_path):
        try:
            with open(file_path, 'r') as file:
                return [line.strip() for line in file]
        except FileNotFoundError:
            messagebox.showerror("Error", f"Dictionary file '{file_path}' not found!")
            return []

    def check_spelling(self):
        input_text = self.input_text_area.get("1.0", tk.END).strip()
        suggestions = self.spell_check(input_text)
        self.output_text_area.config(state='normal')
        self.output_text_area.delete("1.0", tk.END)
        self.output_text_area.insert(tk.END, "\n".join(suggestions))
        self.output_text_area.config(state='disabled')

    def spell_check(self, input_text):
        suggestions = []
        words = input_text.split()
        for word in words:
            word_suggestions = []
            for correct_word in self.dictionary:
                distance = self.wagner_fischer(word, correct_word)
                if distance <= 2:  # Adjust the distance threshold as needed
                    word_suggestions.append(correct_word)
            if word_suggestions:
                suggestions.append(f"Suggestions for '{word}': {', '.join(word_suggestions)}")
            else:
                suggestions.append(f"No suggestions found for: {word}")
        return suggestions

    def wagner_fischer(self, s1, s2):
        # Initialize the matrix
        m, n = len(s1), len(s2)
        dp = [[0] * (n + 1) for _ in range(m + 1)]

        # Fill the first row and first column of the matrix
        for i in range(m + 1):
            dp[i][0] = i
        for j in range(n + 1):
            dp[0][j] = j

        # Compute the Levenshtein distance
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                if s1[i - 1] == s2[j - 1]:
                    dp[i][j] = dp[i - 1][j - 1]
                else:
                    dp[i][j] = min(dp[i - 1][j] + 1,   # Deletion
                    dp[i][j - 1] + 1,   # Insertion
                    dp[i - 1][j - 1] + 1)  # Substitution

        return dp[m][n]

if __name__ == "__main__":
    root = tk.Tk()
    spell_checker = SpellCheckerGUI(root)
    root.mainloop()
