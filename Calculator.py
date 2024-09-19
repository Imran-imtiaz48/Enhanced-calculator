import tkinter as tk
from tkinter import messagebox
import math

class Calculator(tk.Tk):
    def __init__(self):
        super().__init__()

        self.title("Responsive Calculator")
        self.geometry("350x600")
        self.resizable(False, False)

        # Initial state variables
        self.expression = ""
        self.memory = 0
        self.history = []
        self.themes = [
            {"bg": "#2c3e50", "fg": "#ecf0f1"},
            {"bg": "#ecf0f1", "fg": "#2c3e50"},
            {"bg": "#34495e", "fg": "#e74c3c"}
        ]
        self.current_theme_idx = 0

        self.create_widgets()

    def create_widgets(self):
        # Display frame
        self.display_frame = tk.Frame(self, bg=self.themes[self.current_theme_idx]["bg"])
        self.display_frame.grid(row=0, column=0, columnspan=4, sticky="nsew")

        # Expression labels
        self.total_expression = ""
        self.current_expression = ""
        self.total_label, self.label = self.create_display_labels()

        # Button frame
        self.button_frame = tk.Frame(self)
        self.button_frame.grid(row=1, column=0, columnspan=4, sticky="nsew")

        # Configure responsive grid
        self.configure_grid()
        self.create_buttons()
        self.bind_keys()

    def create_display_labels(self):
        total_label = tk.Label(self.display_frame, text=self.total_expression, anchor=tk.E,
                               bg=self.themes[self.current_theme_idx]["bg"], fg=self.themes[self.current_theme_idx]["fg"],
                               padx=24, font=("Arial", 18))
        total_label.grid(row=0, column=0, columnspan=4, sticky="nsew")

        label = tk.Label(self.display_frame, text=self.current_expression, anchor=tk.E,
                         bg=self.themes[self.current_theme_idx]["bg"], fg=self.themes[self.current_theme_idx]["fg"],
                         padx=24, font=("Arial", 32))
        label.grid(row=1, column=0, columnspan=4, sticky="nsew")

        return total_label, label

    def configure_grid(self):
        for i in range(4):
            self.button_frame.grid_columnconfigure(i, weight=1)
        for i in range(10):
            self.button_frame.grid_rowconfigure(i, weight=1)

    def create_buttons(self):
        button_colors = {
            'default': '#34495e',
            'highlight': '#e74c3c',
            'text': '#ecf0f1'
        }

        buttons = [
            ['C', 'CE', '%', '/'],
            ['7', '8', '9', '*'],
            ['4', '5', '6', '-'],
            ['1', '2', '3', '+'],
            ['0', '.', '=', 'π'],
            ['^2', '^3', '√', 'log'],
            ['sin', 'cos', 'tan', 'exp'],
            ['M+', 'M-', 'MR', 'MC'],
            ['!', '1/x', 'deg', 'rad'],
            ['History', 'Quit'],
            ['sinh', 'cosh', 'tanh', 'log2'],
            ['bin', 'oct', 'hex', 'dec'],
            ['Theme', 'Save', 'Load', 'Clear Hist']
        ]

        for r, row in enumerate(buttons):
            for c, button in enumerate(row):
                button_obj = tk.Button(self.button_frame, text=button, font=("Arial", 14), borderwidth=0,
                                       bg=button_colors['default'], fg=button_colors['text'],
                                       activebackground=button_colors['highlight'],
                                       command=lambda x=button: self.on_button_click(x))
                button_obj.grid(row=r, column=c, sticky="nsew", padx=1, pady=1)

    def bind_keys(self):
        key_binds = {
            '<Return>': self.evaluate,
            '<BackSpace>': self.clear_entry,
            '<c>': self.clear,
            '<percent>': lambda _: self.apply_function(lambda x: x / 100),
            '<q>': self.quit,
            '<exclam>': lambda _: self.apply_function(math.factorial),
            '<1>': lambda _: self.apply_function(lambda x: 1 / x),
            '<d>': lambda _: self.apply_function(math.degrees),
            '<r>': lambda _: self.apply_function(math.radians)
        }
        for key, func in key_binds.items():
            self.bind(key, func)

        self.bind('<KeyPress>', self.on_key_press)

    def on_key_press(self, event):
        key = event.char
        key_mappings = {
            '0123456789.': lambda: self.append_value(key),
            '+-*/': lambda: self.append_operator(key),
            'π': lambda: self.append_value(math.pi),
            '^2': lambda: self.apply_function(lambda x: x ** 2),
            '^3': lambda: self.apply_function(lambda x: x ** 3),
            '√': lambda: self.apply_function(math.sqrt),
            'log': lambda: self.apply_function(math.log10),
            'exp': lambda: self.apply_function(math.exp),
            'sin': lambda: self.apply_function(math.sin),
            'cos': lambda: self.apply_function(math.cos),
            'tan': lambda: self.apply_function(math.tan),
            'M+': lambda: self.memory += self.get_value(),
            'M-': lambda: self.memory -= self.get_value(),
            'MR': lambda: self.set_current_expression(self.memory),
            'MC': lambda: self.clear_memory(),
        }
        for keys, action in key_mappings.items():
            if key in keys:
                action()
                break

        self.update_display()

    def on_button_click(self, button):
        button_actions = {
            'C': self.clear, 'CE': self.clear_entry, '=': self.evaluate, '+': self.append_operator,
            '-': self.append_operator, '*': self.append_operator, '/': self.append_operator,
            'π': lambda: self.append_value(math.pi), '^2': lambda: self.apply_function(lambda x: x ** 2),
            '^3': lambda: self.apply_function(lambda x: x ** 3), '√': lambda: self.apply_function(math.sqrt),
            'log': lambda: self.apply_function(math.log10), 'exp': lambda: self.apply_function(math.exp),
            'sin': lambda: self.apply_function(math.sin), 'cos': lambda: self.apply_function(math.cos),
            'tan': lambda: self.apply_function(math.tan), '%': lambda: self.apply_function(lambda x: x / 100),
            'M+': lambda: self.memory += self.get_value(), 'M-': lambda: self.memory -= self.get_value(),
            'MR': lambda: self.set_current_expression(self.memory), 'MC': self.clear_memory, 'History': self.show_history,
            'Quit': self.quit, '!': lambda: self.apply_function(math.factorial), '1/x': lambda: self.apply_function(lambda x: 1 / x),
            'deg': lambda: self.apply_function(math.degrees), 'rad': lambda: self.apply_function(math.radians),
            'sinh': lambda: self.apply_function(math.sinh), 'cosh': lambda: self.apply_function(math.cosh),
            'tanh': lambda: self.apply_function(math.tanh), 'log2': lambda: self.apply_function(math.log2),
            'bin': lambda: self.set_current_expression(bin(int(self.get_value()))),
            'oct': lambda: self.set_current_expression(oct(int(self.get_value()))),
            'hex': lambda: self.set_current_expression(hex(int(self.get_value()))),
            'dec': lambda: self.set_current_expression(str(int(self.current_expression, 0))),
            'Theme': self.change_theme, 'Save': self.save_history, 'Load': self.load_history, 'Clear Hist': self.clear_history
        }
        button_actions.get(button, lambda: self.append_value(button))()
        self.update_display()

    def set_current_expression(self, value):
        self.current_expression = str(value)

    def apply_function(self, func):
        if self.current_expression:
            try:
                value = float(self.current_expression)
                self.current_expression = str(func(value))
                self.add_to_history(self.current_expression)
            except ValueError:
                self.current_expression = "Error"

    def append_value(self, value):
        self.current_expression += str(value)

    def append_operator(self, operator):
        if self.current_expression:
            self.total_expression += self.current_expression + operator
            self.current_expression = ""

    def clear(self):
        self.current_expression = ""
        self.total_expression = ""
        self.add_to_history("Cleared")

    def clear_entry(self):
        self.current_expression = ""

    def evaluate(self):
        self.total_expression += self.current_expression
        try:
            self.current_expression = str(eval(self.total_expression))
            self.total_expression = ""
            self.add_to_history(self.current_expression)
        except Exception:
            self.current_expression = "Error"
            self.add_to_history("Error")

    def get_value(self):
        try:
            return float(self.current_expression)
        except ValueError:
            return 0

    def update_display(self):
        self.label.config(text=self.current_expression[:11])
        self.total_label.config(text=self.total_expression[:24])

    def change_theme(self):
        self.current_theme_idx = (self.current_theme_idx + 1) % len(self.themes)
        theme = self.themes[self.current_theme_idx]
        self.configure(bg=theme["bg"])
        self.total_label.config(bg=theme["bg"], fg=theme["fg"])
        self.label.config(bg=theme["bg"], fg=theme["fg"])
        self.display_frame.config(bg=theme["bg"])

    def clear_memory(self):
        self.memory = 0
        self.add_to_history("Memory cleared")

    def add_to_history(self, expression):
        self.history.append(expression)

    def show_history(self):
        messagebox.showinfo("History", "\n".join(self.history))

    def save_history(self):
        with open("history.txt", "w") as file:
            file.write("\n".join(self.history))
        messagebox.showinfo("Saved", "History saved to history.txt")

    def load_history(self):
        try:
            with open("history.txt", "r") as file:
                self.history = file.read().splitlines()
            messagebox.showinfo("Loaded", "History loaded from history.txt")
        except FileNotFoundError:
            messagebox.showerror("Error", "No history file found")

    def clear_history(self):
        self.history = []
        messagebox.showinfo("Cleared", "History cleared")

if __name__ == "__main__":
    app = Calculator()
    app.mainloop()
