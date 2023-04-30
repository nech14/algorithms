from enum import Enum
import struct


class Alignment(Enum):
    HORIZONTAL = 1
    VERTICAL = 2


class Widget():

    def __init__(self, parent):
        self.parent = parent
        self.childrens = []

        if self.parent is not None:
            self.parent.add_children(self)

    def getParent(self):
        return self.parent

    def getChildrens(self):
        return self.childrens

    def getAlignment(self):
        return self.alignment
    
    def add_children(self, children: "Widget"):
        self.childrens.append(children)

    def to_binary(self, generation=0, count_brother=0):
        result = ""
        d = {'MainWindow': 0, 'Layout':1, 'LineEdit':2, 'ComboBox':3}

        classname = self.__class__.__name__

        match classname:
            case 'MainWindow':
                result += '0'
                result += self.title
            case 'Layout':
                result += '1'
                result += str(generation)
                result += '/'                
                if str(self.alignment)[10:] == 'HORIZONTAL':
                    result += '1'
                else:
                    result += '2'
                generation += 1 + count_brother
            case 'LineEdit':
                result += '2'
                result += str(generation)
                result += '/'
                result += str(self.max_length)
                generation += 1 + count_brother
            case 'ComboBox':
                result += '3'
                result += str(generation)
                result += '/'
                #result += str(self.items)
                result += "/".join(map(str, self.items))
                generation += 1 + count_brother
        result += '//'

        count_childrens = len(self.getChildrens())
        for i in range(count_childrens):
            result += self.getChildrens()[i].to_binary(generation, i)
        
        return result

    @classmethod
    def from_binary(self, data, number=0, history=[], buf_generation = [0]):
        buf = data[number]
        classname = buf
        hbuf = -1
        match classname:
            case '0':
                title = ''
                while buf != '/' and data[number+1] != '/':
                    number += 1
                    buf = data[number]
                    title += buf                
                select = MainWindow(title)
                history.append(select)
            case '1':
                number += 1
                hbuf = int(data[number])
                number += 2
                alignment = int(data[number])
                select = Layout(history[hbuf], Alignment(alignment))
                position = 1 + buf_generation[hbuf]
                for i in range(hbuf):
                    position += buf_generation[i]
                history.insert(position, select)
            case '2':
                number += 1
                hbuf = int(data[number])
                max_length = ""
                number += 2
                buf = data[number]
                while buf != '/' and data[number+1] != '/':
                    max_length += buf
                    number += 1
                    buf = data[number]
                   
                select = LineEdit(history[hbuf], int(max_length))
                
                if len(buf_generation) < hbuf+1:
                    buf_generation.append(0)
                position = 1 + buf_generation[hbuf]
                for i in range(hbuf):
                    position += buf_generation[i]
                history.insert(position, select)
            case '3':
                number += 1
                hbuf = int(data[number])
                items = []
                number += 2
                buf = data[number]
                while not(buf == '/' and data[number-1] == '/'):
                    item = ''
                    while buf != '/':
                        item += buf
                        number += 1
                        buf = data[number]
                    items.append(item)
                    number += 1
                    buf = data[number]
                select = ComboBox(history[hbuf], items)
                if len(buf_generation) < hbuf+1:
                    buf_generation.append(0)
                position = 1 + buf_generation[hbuf]
                for i in range(hbuf):
                    position += buf_generation[i]
                history.insert(position, select)
                number -= 2
        number += 3

        if len(buf_generation) < hbuf+1:
            buf_generation.append(1)
        elif hbuf >= 0:
            buf_generation[hbuf] += 1
        if number < len(data):
            self.from_binary(data, number, history, buf_generation)
        return history[0]

    def __str__(self):
        return f"{self.__class__.__name__}{self.childrens}"

    def __repr__(self):
        return str(self)

class MainWindow(Widget):

    def __init__(self, title: str):
        super().__init__(None)
        self.title = title

class Layout(Widget):

    def __init__(self, parent, alignment: Alignment):
        super().__init__(parent)
        self.alignment = alignment

class LineEdit(Widget):

    def __init__(self, parent, max_length: int=10):
        super().__init__(parent)
        self.max_length = max_length

    

class ComboBox(Widget):

    def __init__(self, parent, items):
        super().__init__(parent)
        self.items = items

app = MainWindow("Application")
layout1 = Layout(app, Alignment.HORIZONTAL)
layout2 = Layout(app, Alignment.VERTICAL)

edit1 = LineEdit(layout1, 20)
edit2 = LineEdit(layout1, 30)

box1 = ComboBox(layout2, [1, 2, 3, 4])
box2 = ComboBox(layout2, ["a", "b", "c"])

print(f"app: {app}")

bts = app.to_binary()

print(f"Binary data: {bts}")
print(f"Binary data length: {len(bts)}")
new_app = MainWindow.from_binary(bts)
print(f"new_app: {new_app}")

