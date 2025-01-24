import tkinter as tk
import math
import pyperclip

class Calculator(tk.Tk):
    def __init__(self):
        super().__init__()

        self.title("Enhanced Calculator")
        self.geometry("400x650")
        self.resizable(True, True)
        self.configure(bg="#1e1e1e")

        self.expression = ""
        self.memory = 0
        self.history = []

        self.create_widgets()
    
    def create_widgets(self):
        # Display Frame
        self.display_frame = tk.Frame(self, bg="#333333")
        self.display_frame.pack(expand=True, fill="both", padx=10, pady=10)

        self.total_label = tk.Label(self.display_frame, text="", anchor=tk.E, bg="#333333", fg="#ffffff", padx=20, font=("Arial", 18))
        self.total_label.pack(fill="both")

        self.label = tk.Label(self.display_frame, text="", anchor=tk.E, bg="#333333", fg="#ffffff", padx=20, font=("Arial", 32, "bold"))
        self.label.pack(fill="both")

        # Button Frame
        self.button_frame = tk.Frame(self, bg="#1e1e1e")
        self.button_frame.pack(expand=True, fill="both")

        self.create_buttons()

        # Bind keys for keyboard shortcuts
        self.bind_keys()
    
    def create_buttons(self):
        button_colors = {
            'default': '#4a4a4a',
            'highlight': '#ff9800',
            'text': '#ffffff'
        }

        buttons = [
            ['C', 'CE', '⌫', '/'],
            ['7', '8', '9', '*'],
            ['4', '5', '6', '-'],
            ['1', '2', '3', '+'],
            ['0', '.', '=', 'π'],
            ['^2', '^3', '√', 'log'],
            ['sin', 'cos', 'tan', 'exp'],
            ['M+', 'M-', 'MR', 'MC'],
            ['1/x', '(', ')', 'History'],
            ['Copy', 'Paste', 'Quit']
        ]

        for r, row in enumerate(buttons):
            for c, button in enumerate(row):
                tk.Button(
                    self.button_frame,
                    text=button,
                    font=("Arial", 14),
                    borderwidth=1,
                    relief="raised",
                    bg=button_colors['default'],
                    fg=button_colors['text'],
                    activebackground=button_colors['highlight'],
                    command=lambda x=button: self.on_button_click(x)
                ).grid(row=r, column=c, sticky="nsew", padx=5, pady=5)

        for i in range(len(buttons)):
            self.button_frame.grid_rowconfigure(i, weight=1)
        for i in range(4):
            self.button_frame.grid_columnconfigure(i, weight=1)

    def bind_keys(self):
        self.bind('<Return>', lambda event: self.evaluate())
        self.bind('<BackSpace>', lambda event: self.clear_entry())
        self.bind('<Escape>', lambda event: self.quit())
        self.bind('<Control-c>', lambda event: self.copy_to_clipboard())
        self.bind('<Control-v>', lambda event: self.paste_from_clipboard())

    def on_button_click(self, button):
        if button == 'C':
            self.clear()
        elif button == 'CE':
            self.clear_entry()
        elif button == '⌫':
            self.backspace()
        elif button == '=':
            self.evaluate()
        elif button in ('+', '-', '*', '/'):
            self.append_operator(button)
        elif button == 'π':
            self.append_value(math.pi)
        elif button == '^2':
            self.apply_function(lambda x: x ** 2)
        elif button == '^3':
            self.apply_function(lambda x: x ** 3)
        elif button == '√':
            self.apply_function(math.sqrt)
        elif button == 'log':
            self.apply_function(math.log10)
        elif button == 'exp':
            self.apply_function(math.exp)
        elif button == 'sin':
            self.apply_function(math.sin)
        elif button == 'cos':
            self.apply_function(math.cos)
        elif button == 'tan':
            self.apply_function(math.tan)
        elif button == '1/x':
            self.apply_function(lambda x: 1 / x)
        elif button == 'M+':
            self.memory += self.get_value()
        elif button == 'M-':
            self.memory -= self.get_value()
        elif button == 'MR':
            self.current_expression = str(self.memory)
        elif button == 'MC':
            self.memory = 0
        elif button == 'History':
            self.show_history()
        elif button == 'Copy':
            self.copy_to_clipboard()
        elif button == 'Paste':
            self.paste_from_clipboard()
        elif button == 'Quit':
            self.quit()
        else:
            self.append_value(button)

        self.update_display()

    def append_value(self, value):
        self.expression += str(value)
        self.update_display()

    def append_operator(self, operator):
        if self.expression:
            self.expression += operator
            self.update_display()

    def clear(self):
        self.expression = ""
        self.update_display()

    def clear_entry(self):
        self.expression = self.expression[:-1]
        self.update_display()

    def backspace(self):
        self.expression = self.expression[:-1]
        self.update_display()

    def evaluate(self):
        try:
            self.expression = str(eval(self.expression))
            self.history.append(self.expression)
        except Exception:
            self.expression = "Error"
        self.update_display()

    def apply_function(self, func):
        try:
            value = float(self.expression)
            self.expression = str(func(value))
            self.history.append(self.expression)
        except ValueError:
            self.expression = "Error"
        self.update_display()

    def get_value(self):
        try:
            return float(self.expression)
        except ValueError:
            return 0

    def copy_to_clipboard(self):
        pyperclip.copy(self.expression)

    def paste_from_clipboard(self):
        clipboard_content = pyperclip.paste()
        self.append_value(clipboard_content)

    def show_history(self):
        history_window = tk.Toplevel(self)
        history_window.title("Calculation History")
        history_window.geometry("300x400")

        history_list = tk.Listbox(history_window, bg="#2c2c2c", fg="white", font=("Arial", 14))
        history_list.pack(expand=True, fill="both")

        for entry in self.history[-10:]:
            history_list.insert(tk.END, entry)

    def update_display(self):
        self.label.config(text=self.expression)

if __name__ == "__main__":
    calculator = Calculator()
    calculator.mainloop()
