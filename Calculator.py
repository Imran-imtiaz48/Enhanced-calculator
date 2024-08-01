import tkinter as tk
import math

class Calculator(tk.Tk):
    def __init__(self):
        super().__init__()

        self.title("Responsive Calculator")
        self.geometry("350x500")  # Adjusted initial width and height
        self.resizable(False, False)  # Disable resizing to avoid extra space

        self.expression = ""
        self.memory = 0
        self.history = []

        self.create_widgets()

    def create_widgets(self):
        # Display Frame
        self.display_frame = tk.Frame(self, bg="#2c3e50")
        self.display_frame.grid(row=0, column=0, columnspan=4, sticky="nsew")

        self.total_expression = ""
        self.current_expression = ""

        self.total_label, self.label = self.create_display_labels()

        # Button Frame
        self.button_frame = tk.Frame(self)
        self.button_frame.grid(row=1, column=0, columnspan=4, sticky="nsew")

        self.create_buttons()

        # Configure grid weights
        self.grid_rowconfigure(0, weight=1)
        self.grid_rowconfigure(1, weight=1)
        self.grid_columnconfigure(0, weight=1)

        for i in range(9):  # Updated to reflect the number of button rows
            self.button_frame.grid_rowconfigure(i, weight=1)
        for i in range(4):  # Updated to reflect the number of button columns
            self.button_frame.grid_columnconfigure(i, weight=1)

        self.bind_keys()

    def create_display_labels(self):
        total_label = tk.Label(self.display_frame, text=self.total_expression, anchor=tk.E, bg="#2c3e50", fg="#ecf0f1", padx=24, font=("Arial", 18))
        total_label.grid(row=0, column=0, columnspan=4, sticky="nsew")

        label = tk.Label(self.display_frame, text=self.current_expression, anchor=tk.E, bg="#2c3e50", fg="#ecf0f1", padx=24, font=("Arial", 32))
        label.grid(row=1, column=0, columnspan=4, sticky="nsew")

        return total_label, label

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
            ['History', 'Quit']
        ]

        for r, row in enumerate(buttons):
            for c, button in enumerate(row):
                button_obj = tk.Button(
                    self.button_frame,
                    text=button,
                    font=("Arial", 14),
                    borderwidth=0,
                    bg=button_colors['default'],
                    fg=button_colors['text'],
                    activebackground=button_colors['highlight'],
                    command=lambda x=button: self.on_button_click(x)
                )
                button_obj.grid(row=r, column=c, sticky="nsew", padx=1, pady=1)  # Minimized padding

    def bind_keys(self):
        # Bind key events for numbers, operators, and special keys
        self.bind('<KeyPress>', self.on_key_press)
        self.bind('<Return>', lambda event: self.evaluate())  # Enter key
        self.bind('<BackSpace>', lambda event: self.clear_entry())  # Backspace key
        self.bind('<c>', lambda event: self.clear())  # Clear key (c or C)
        self.bind('<percent>', lambda event: self.apply_function(lambda x: x / 100))  # Percent key
        self.bind('<q>', lambda event: self.quit())  # Quit key (q)

    def on_key_press(self, event):
        key = event.char
        if key in '0123456789.':
            self.append_value(key)
        elif key in '+-*/':
            self.append_operator(key)
        elif key == '\r':  # Enter key
            self.evaluate()
        elif key == '\x08':  # Backspace key
            self.clear_entry()
        elif key == 'c' or key == 'C':
            self.clear()
        elif key == '%':
            self.apply_function(lambda x: x / 100)
        elif key == 'q':
            self.quit()
        elif key == 'p':  # π key
            self.append_value(math.pi)
        elif key == '^':  # Square or Cube
            if event.keysym == '2':
                self.apply_function(lambda x: x ** 2)
            elif event.keysym == '3':
                self.apply_function(lambda x: x ** 3)
        elif key == 'r':  # Square Root key
            self.apply_function(math.sqrt)
        elif key == 'l':  # Logarithm key
            self.apply_function(math.log10)
        elif key == 'e':  # Exponent key
            self.apply_function(math.exp)
        elif key == 's':  # Sine key
            self.apply_function(math.sin)
        elif key == 'c':  # Cosine key
            self.apply_function(math.cos)
        elif key == 't':  # Tangent key
            self.apply_function(math.tan)
        elif key == 'm':  # Memory add key (M+)
            self.memory += self.get_value()
        elif key == 'M':  # Memory recall key (MR)
            self.current_expression = str(self.memory)
        elif key == 'M' and event.keysym == 'minus':  # Memory subtract key (M-)
            self.memory -= self.get_value()
        elif key == 'h':  # History key
            self.show_history()
        elif key == 'q':  # Quit key
            self.quit()

        self.update_display()

    def on_button_click(self, button):
        if button == 'C':
            self.clear()
        elif button == 'CE':
            self.clear_entry()
        elif button == '=':
            self.evaluate()
        elif button in ['+', '-', '*', '/']:
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
        elif button == '%':
            self.apply_function(lambda x: x / 100)
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
        elif button == 'Quit':
            self.quit()
        else:
            self.append_value(button)

        self.update_display()

    def apply_function(self, func):
        if self.current_expression != "":
            try:
                value = float(self.current_expression)
                self.current_expression = str(func(value))
                self.add_to_history(self.current_expression)
            except ValueError:
                self.current_expression = "Error"

    def append_value(self, value):
        self.current_expression += str(value)

    def append_operator(self, operator):
        if self.current_expression == "":
            return
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
        except Exception as e:
            self.current_expression = "Error"
            self.add_to_history("Error")

    def get_value(self):
        try:
            return float(self.current_expression)
        except ValueError:
            return 0

    def add_to_history(self, entry):
        self.history.append(entry)
        if len(self.history) > 10:
            self.history.pop(0)

    def show_history(self):
        history_window = tk.Toplevel(self)
        history_window.title("History")
        history_window.geometry("300x400")

        history_list = tk.Listbox(history_window)
        history_list.pack(expand=True, fill="both")

        for entry in self.history:
            history_list.insert(tk.END, entry)

    def update_display(self):
        self.total_label.config(text=self.total_expression)
        self.label.config(text=self.current_expression)

if __name__ == "__main__":
    calculator = Calculator()
    calculator.mainloop()
