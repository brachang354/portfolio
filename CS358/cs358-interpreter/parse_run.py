#Bradley Chang
#Parser Milestone 2
#2/18/2025

"""
This file will serve as the parser for my Turtle domain as well as support for boolean
expressions and arithmetic expressions.
At the very end of this file there is a main where you can put expressions into
the function parse_and_run to test out various expressions.

***MILESTONE 2 CHANGES***
***For the "Evaluation always produces a value" portion of rubric ***
I also notably changed my operators around since Milestone 1. Instead of using pen color I 
now decided to have a rotate operator instead since when evaluating a color it was possible 
to get back a string which is not considered a value type. I did keep around the 
pen size however since that does evaluate to get back an int.
"""
from interp import Add, Sub, Mul, Div, Neg, Let, Name, Lit, Expr, Forward, Left, Back, \
Right, Color, PenSize, And, Or, Not, Eq, Lt, If, Append, Repeat, AddColor, SetSize, Rotate, Letfun, App, Seq, Show, Read, run

from lark import Lark, Token, ParseTree, Transformer
from lark.exceptions import VisitError
from pathlib import Path
#import readline # type: ignore  # allows editing and history for input()

parser = Lark(Path('expr.lark').read_text(),start='expr',ambiguity='explicit')

class ParseError(Exception):
    pass

def parse(s:str) -> ParseTree:
    try:
        return parser.parse(s)
    except Exception as e:
        raise ParseError(e)

class AmbiguousParse(Exception):
    pass

class ToExpr(Transformer[Token,Expr]):
    '''Defines a transformation from a parse tree into an AST'''
    def plus(self, args:tuple[Expr,Expr]) -> Expr:
        return Add(args[0],args[1])
    def minus(self, args:tuple[Expr,Expr]) -> Expr:
        return Sub(args[0],args[1])
    def times(self, args:tuple[Expr,Expr]) -> Expr:
        return Mul(args[0],args[1])
    def divide(self, args:tuple[Expr,Expr]) -> Expr:
        return Div(args[0],args[1])
    def neg(self, args:tuple[Expr]) -> Expr:
        return Neg(args[0])           
    
    #Boolean and relational expressions 
    def and_(self, args:tuple[Expr,Expr]) -> Expr:
        return And(args[0],args[1])
    def or_(self, args:tuple[Expr,Expr]) -> Expr:
        return Or(args[0],args[1])
    def not_(self, args:tuple[Expr]) -> Expr:
        return Not(args[0])  
    def eq(self, args:tuple[Expr,Expr]) -> Expr:
        return Eq(args[0],args[1])
    def lt(self, args:tuple[Expr,Expr]) -> Expr:
        return Lt(args[0],args[1])
    
    #Turtle expressions
    def forward(self, args:tuple[Expr]) -> Expr:
        return Lit(Forward(int(args[0].value)))
    def back(self, args:tuple[Expr]) -> Expr:
        return Lit(Back(int(args[0].value)))
    def left(self, args:tuple[Expr]):
        return Lit(Left(int(args[0].value)))
    def right(self, args:tuple[Expr]):
        return Lit(Right(int(args[0].value))) 
    def append(self, args:tuple[Expr,Expr]) -> Expr:
        return Append(args[0],args[1]) 
    def repeat(self, args:tuple[Expr,Expr]) -> Expr:
        return Repeat(args[0],args[1]) 
    def rotate(self, args:tuple[Expr,Expr]) -> Expr:
        return Rotate(args[0],args[1]) 
#    def color(self, args:tuple[Expr,Expr]) -> Expr:
#        return Color(args[0],args[1])
    def color(self, args:tuple[Expr]) -> Expr:
        #return Color(args[0])
        return Lit(Color(str(args[0].value)))
    def add_color(self, args:tuple[Expr,Expr]) -> Expr:
        return AddColor(args[0],args[1]) 
#    def pen_size(self, args:tuple[Expr,Expr]) -> Expr:
#        return PenSize(args[0],args[1]) 
    def pen_size(self, args:tuple[Expr]) -> Expr:
        return Lit(PenSize(int(args[0].value)))
    def set_size(self, args:tuple[Expr,Expr]) -> Expr:
        return SetSize(args[0],args[1]) 

    def if_(self,args:tuple[Expr,Expr,Expr]) -> Expr:
        return If(args[0],args[1],args[2])
    def letfun(self,args:tuple[Token,Token,Expr,Expr]) -> Expr:
        return Letfun(args[0].value,args[1].value,args[2],args[3])
    def app(self,args:tuple[Expr,Expr]) -> Expr:
        return App(args[0],args[1])     
    def let(self, args:tuple[Token,Expr,Expr]) -> Expr:
        return Let(args[0].value,args[1],args[2]) 
    def id(self, args:tuple[Token]) -> Expr:
        if args[0].value == "true":
            return Lit(True)
        elif args[0].value == "false":
            return Lit(False)
        elif args[0].value == "read":
            return Read()
        else:
            return Name(args[0].value)
    def int(self,args:tuple[Token]) -> Expr:
        return Lit(int(args[0].value))
    def string(self, args:tuple[Token]) -> Expr:
        value = args[0].value[1:-1]
        return Lit(value)
    def seq(self,args:tuple[Expr,Expr]) -> Expr:
        return Seq(args[0],args[1])
    
    def show(self, args:tuple[Expr]) -> Expr:
        return Show(args[0])

    def _ambig(self,_) -> Expr:    # ambiguity marker
        raise AmbiguousParse()


def genAST(t:ParseTree) -> Expr:
    '''Applies the transformer to convert a parse tree into an AST'''
    # boilerplate to catch potential ambiguity error raised by transformer
    try:
        return ToExpr().transform(t)               
    except VisitError as e:
        if isinstance(e.orig_exc,AmbiguousParse):
            raise AmbiguousParse()
        else:
            raise e

def parse_and_run(s:str):
#while True:
    try:
        #s = input('expr: ')
        t = parse(s)
        print("raw:", t)    
        print("pretty:")
        print(t.pretty())
        ast = genAST(t)
        print("raw AST:", repr(ast))  # use repr() to avoid str() pretty-printing
        run(ast)                      # pretty-prints and executes the AST
    except AmbiguousParse:
        print("ambiguous parse")                
    except ParseError as e:
        print("parse error:")
        print(e)
    except EOFError:
        pass

def just_parse(s:str):
    try:
        #s = input('expr: ')
        t = parse(s)
        print("raw:", t)    
        print("pretty:")
        print(t.pretty())
        ast = genAST(t)
        print("raw AST:", repr(ast))  # use repr() to avoid str() pretty-printing
    except AmbiguousParse:
        print("ambiguous parse")                
    except ParseError as e:
        print("parse error:")
        print(e)
        return None
    except EOFError:
        pass

def driver():
    while True:
        try:
            s = input('expr: ')
            while s[-1] == '\\':
                s = s[:-1] + '\n' + input('... ')    
            t = parse(s)
            print("raw:", t)    
            print("pretty:")
            print(t.pretty())
            ast = genAST(t)
            print("raw AST:", repr(ast))  # use repr() to avoid str() pretty-printing
            run(ast)                      # pretty-prints and executes the AST
        except AmbiguousParse:
            print("ambiguous parse")                
        except ParseError as e:
            print("parse error:")
            print(e)
        except EOFError:
            break

def main():
    parse_and_run("x && y")
    parse_and_run("show 10 + 15")
    
    parse_and_run('~15 ~~ (4 @ (^200 ++ <90))')
    parse_and_run('%"lime" %% (4 @ (^200 ++ <90))')
    """
    parse_and_run("2 * 3 + 10")
    parse_and_run("If 5 < 10 then true else false")
    parse_and_run("letfun add(x) = x + 5 in add(5) end")
    parse_and_run("If true || false then true else false")
    parse_and_run("true && false")
    parse_and_run("4 @ (^100 ++ <90)")
    parse_and_run("45 # (4 @ (^100 ++ <90))")
    parse_and_run('~15 ~~ (4 @ (^200 ++ <90))')
    """

if __name__=="__main__":
    main()