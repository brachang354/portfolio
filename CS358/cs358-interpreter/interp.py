#Bradley Chang 
#CS 358
#1/27/2025

"""
This is the interpreter for the Python Turtle domain which will require an installation
of Python with Turtle graphics. 

At the end of the file there are some test expressions of various shapes that can be run to
test the interpreter. You can also create new expressions to test out if you'd like, 
just remember to put run statements at the very bottom to test them out.

The very bottom of this file will have the statements
where the test expressions are being run, some of them are commented out.

When you run this file it will pop out a new window which will draw out some of the
various shapes described in the expressions below.

If you are running the test script make sure to close the Turtle window after its done 
so that the tests can run.

***MILESTONE 3***
Milestone 3 has been quite rough, and is very incomplete. I could use some pointers on 
trying to fix things. I gave my best attempt at making the variables mutable, adding show()
and read() operators, and tried to get AddColor for my Turtle working. I also organized the driver
area by including a just_parse, and driver.
"""
import turtle as t
import time
from dataclasses import dataclass

type Action = Forward | Left | Back | Right | Color | PenSize

@dataclass
class Forward():
    distance: int
    def __str__(self) -> str:
        return f"Forward({self.distance})"
    
@dataclass
class Back():
    distance: int
    def __str__(self) -> str:
        return f"Back({self.distance})"
    
@dataclass
class Left():
    angle: int
    def __str__(self) -> str:
        return f"Left({self.angle})"
    
@dataclass
class Right():
    angle: int
    def __str__(self) -> str:
        return f"Right({self.angle})"
   
@dataclass
class Color():
    color: str
    def __str__(self) -> str:
        return f"Color({self.color})"
    
@dataclass
class PenSize():
    pensize: int
    def __str__(self) -> str:
        return f"Pen Size ({self.pensize})"

type Literal = int | Action

type Expr = Add | Sub | Mul | Div | Neg | Lit | Let | Name | And | Or | Not | Eq | Lt | If | Append | Repeat \
    | AddColor | SetSize | Rotate | Letfun | App | Assign | Seq | Read | Show


#Definitions of all expressions
@dataclass
class Add():
    left: Expr
    right: Expr
    def __str__(self) -> str:
        return f"({self.left} + {self.right})"

@dataclass
class Sub():
    left: Expr
    right: Expr
    def __str__(self) -> str:
        return f"({self.left} - {self.right})"

@dataclass
class Mul():
    left: Expr
    right: Expr
    def __str__(self) -> str:
        return f"({self.left} * {self.right})"

@dataclass
class Div():
    left: Expr
    right: Expr
    def __str__(self) -> str:
        return f"({self.left} / {self.right})"

@dataclass
class Neg():
    subexpr: Expr
    def __str__(self) -> str:
        return f"(- {self.subexpr})"
    
# The unary operator Neg has a single operand
@dataclass
class Neg():
    subexpr: Expr
    def __str__(self) -> str:
        return f"(- {self.subexpr})"

# Literals are just integers
@dataclass
class Lit():
    value: int
    def __str__(self) -> str:
        return f"{self.value}"

# Let bindings have a name, a definition expression, and a body expression
@dataclass
class Let():
    name: str
    defexpr: Expr
    bodyexpr: Expr
    def __str__(self) -> str:
        return f"(let {self.name} = {self.defexpr} in {self.bodyexpr})"

# Names are just strings referencing a let binding
@dataclass
class Name():
    name:str
    def __str__(self) -> str:
        return self.name
    
@dataclass
class And():
    left: Expr
    right: Expr
    def __str__(self) -> str:
        return f"({self.left} And {self.right})"
    
@dataclass
class Or():
    left: Expr
    right: Expr
    def __str__(self) -> str:
        return f"({self.left} Or {self.right})"
    
@dataclass
class Not():
    subexpr: Expr
    def __str__(self) -> str:
        return f"(not {self.subexpr})"
    
@dataclass
class Eq():
    left: Expr
    right: Expr
    def __str__(self) -> str:
        return f"({self.left} Equals {self.right})"
    
@dataclass
class Lt():
    left: Expr
    right: Expr
    def __str__(self) -> str:
        return f"({self.left} is less than {self.right})"

@dataclass
class If():
    cond: Expr
    thenexpr: Expr
    elseexpr: Expr
    def __str__(self) -> str:
        return f"(if {self.cond} then {self.thenexpr} else {self.elseexpr})"

#Letfun and App stuff for new Milestone
@dataclass
class Letfun():
    name: str
    param: str
    bodyexpr: Expr
    inexpr: Expr
    def __str__(self) -> str:
        return f"letfun {self.name} ({self.param}) = {self.bodyexpr} in {self.inexpr} end"

@dataclass
class App():
    fun: Expr
    arg: Expr
    def __str__(self) -> str:
        return f"({self.fun} ({self.arg}))"

#Append, Repeat, AddColor, and SetSize are all Turtle specific operators    
@dataclass
class Append():
    #color: Expr
    left: Expr
    right: Expr
    def __str__(self) -> str:
        #return f"({self.color}, {self.left} ++ {self.right})"
        return f"({self.left} ++ {self.right})"
@dataclass
class Repeat():
    count: Expr
    path: Expr
    def __str__(self) -> str:
        return f"({self.count} @ {self.path})"

@dataclass
class Rotate():
    degrees: Expr
    path: Expr
    def __str__(self) -> str:
        return f"({self.degrees} % {self.path})"    

@dataclass
class AddColor():
    color: Expr
    path: Expr
    def __str__(self) -> str:
        return f"({self.color} color with {self.path})"

@dataclass
class SetSize():
    size: Expr
    path: Expr
    def __str__(self) -> str:
        return f"({self.size} size with {self.path})"
    
@dataclass
class Assign():
    name: str
    expr: Expr
    def __str__(self) -> str:
        return f"{self.name} := {self.expr}"
    
@dataclass
class Seq():
    expr1: Expr
    expr2: Expr
    def __str__(self) -> str:
        return f"({self.expr1}; {self.expr2})"

@dataclass
class Read():
    #input1: str
    def __str__(self) -> str:
        return f"(Input: )"

@dataclass
class Show():
    expr1: Expr
    def __str__(self) -> str:
        return f"(Running: {self.expr1})"

#@dataclass
#class Subpath():
#    left: Expr
#    right: Expr
#    def __str__(self) -> str:
#        #return f"({self.color}, {self.left} ++ {self.right})"
#        return f"({self.left} -- {self.right})"
    


type Binding[V] = tuple[str,V]  # this tuple type is always a pair
type Env[V] = tuple[Binding[V], ...] # this tuple type has arbitrary length 

from typing import Any
emptyEnv : Env[Any] = ()  # the empty environment has no bindings

def extendEnv[V](name: str, value: V, env:Env[V]) -> Env[V]:
    '''Return a new environment that extends the input environment env with a new binding from name to value'''
    return ((name,value),) + env

def lookupEnv[V](name: str, env: Env[V]) -> (V | None) :
    '''Return the first value bound to name in the input environment env
       (or raise an exception if there is no such binding)'''
    # exercises2b.py shows a different implementation alternative
    match env:
        case ((n,v), *rest) :
            if n == name:
                return v
            else:
                return lookupEnv(name, rest) # type:ignore
        case _ :
            return None        

# Location methods to help make variables mutable
type Loc[V] = list[V] # always a singleton list
def newLoc[V](value: V) -> Loc[V]:
    return [value]
def getLoc[V](loc: Loc[V]) -> V:
    return loc[0]
def setLoc[V](loc: Loc[V], value: V) -> None:
    loc[0] = value
        
class EvalError(Exception):
    pass

@dataclass
class Path:
    p: tuple[Action, ...]

type Value = int | Path | Closure | str

@dataclass
class Closure:
    param: str
    body: Expr
    env: Env[Value]

def eval(e: Expr) -> Value :
    return evalInEnv(emptyEnv, e)

#This is where we will be performing the actual operations. 
#We will also handle any errors that occur with type mismatches such as adding a bool and an int
#or comparing a bool to an int.
def evalInEnv(env: Env[Value], e:Expr) -> Value:
    match e:
        case Add(l,r):            
            leftVal = evalInEnv(env, l)
            rightVal = evalInEnv(env, r)
            if type(leftVal) != int or type(rightVal) != int:
                raise EvalError ("addition of non-integers")
            else:
                return leftVal + rightVal
        case Sub(l,r):
            leftVal = evalInEnv(env, l)
            rightVal = evalInEnv(env, r)
            if type(leftVal) != int or type(rightVal) != int:
                raise EvalError ("subtraction of non-integers")
            else:
                return leftVal - rightVal
        case Mul(l,r):
            leftVal = evalInEnv(env, l)
            rightVal = evalInEnv(env, r)
            if type(leftVal) != int or type(rightVal) != int:
                raise EvalError ("multiplication of non-integers")
            else:
                return leftVal * rightVal
        case Div(l,r):
            leftVal = evalInEnv(env, l)
            rightVal = evalInEnv(env, r)
            if type(leftVal) != int or type(rightVal) != int:
                raise EvalError ("division of non-integers")
            else:
                return leftVal // rightVal
               
        case Neg(s):
            if type(evalInEnv(env, s)) != int:
                raise EvalError("negation of non-integer")
            return - (evalInEnv(env,s))

        case(Lit(lit)):
            match lit:  # two-level matching keeps type-checker happy
                case int(i):
                    return i
                case Forward(_) as a:
                    return Path((a,))
                case Left(_) as a:
                    return Path((a,))
                case Back(_) as a:
                    return Path((a,))
                case Right(_) as a:
                    return Path((a,))
                case Color(c):
                    return c
                case PenSize(s):
                    return s
                
        #Append, repeat AddColor, and SetSize are the Turtle domain specific operations.
        case Append(l,r):
            match (evalInEnv(env,l), evalInEnv(env,r)):
                case (Path(pl), Path(pr)):
                    return Path(pl + pr)
                case _:
                    raise EvalError("append of non-paths")
        case Repeat(c,p):   
            match (evalInEnv(env,c), evalInEnv(env,p)):
                case (int(i),Path(pl)):
                    return Path(pl * i)
                case _:
                    raise EvalError("repeat of non-path")
        case Rotate(c,p):   
            match (evalInEnv(env,c), evalInEnv(env,p)):
                case (int(i),Path(pr)):
                    return Path((Right(i),) + pr)
                case _:
                    raise EvalError("rotate of non-path")
        #This will set the color of the pen
        case AddColor(c, p):
            match (evalInEnv(env, c), evalInEnv(env, p)):
                case (str(cl), Path(pr)):
                    return Path((Color(cl),) + pr)
                case _:
                    raise EvalError("adding color of non-path")
        #This will set the size of the pen
        case SetSize(s, p):
            match (evalInEnv(env, s), evalInEnv(env, p)):
                case (int(s1), Path(pr)):
                    return Path((PenSize(s1),) + pr)
                case _:
                    raise EvalError("Setting size of non-path")
            
        #case Subpath(l,r):
        #    match (evalInEnv(env,l), evalInEnv(env,r)):
        #        case (Path(pl), Path(pr)):
        #            return Path(pl - pr)
        #        case _:
        #            raise EvalError("subtraction of non-paths")

        case Name(n):
            '''
            v = lookupEnv(n, env)
            if v is None:
                raise EvalError(f"unbound name {n}")
            return v
            '''
            l = lookupEnv(n, env)
            if l is None:
                raise EvalError(f"unbound name {n}")
            return getLoc(l)
            
        case Let(n,d,b):
            v = evalInEnv(env, d)
            loc = newLoc(v)
            newEnv = extendEnv(n, loc, env)
            return evalInEnv(newEnv, b)
            #v = evalInEnv(env, d)
            #newEnv = extendEnv(n, v, env)
            #return evalInEnv(newEnv, b)
        
        case And(l, r):
            leftVal = evalInEnv(env, l)
            if type(leftVal) != bool:
                raise EvalError("Not bool")
            if leftVal == False: #Short Circuit
                return False
            rightVal = evalInEnv(env, r)
            if type(rightVal) != bool:
                raise EvalError("Not bool")
            return leftVal and rightVal
        
        case Or(l, r):
            leftVal = evalInEnv(env, l)
            if type(leftVal) != bool:
                raise EvalError("Not bool")
            if leftVal == True:
                return True
            rightVal = evalInEnv(env, r)
            if type(rightVal) != bool:
                raise EvalError("Not bool")
            return leftVal or rightVal
        
        case Not(s):
            if type(evalInEnv(env, s)) != bool:
                raise EvalError("Not bool")
            return not evalInEnv(env, s)
        
        case Eq(l, r):
            leftVal = evalInEnv(env, l)
            rightVal = evalInEnv(env, r)
            if(type(leftVal) != type(rightVal)):
                return False
            return leftVal == rightVal
        
        case Lt(l, r):
            leftVal = evalInEnv(env, l)
            if type(leftVal) != int:
                raise EvalError("Not int")
            rightVal = evalInEnv(env, r)
            if type(rightVal) != int:
                raise EvalError("Not int")
            return leftVal < rightVal
        
        case If(cond, thenexpr, elseexpr):
            if type(evalInEnv(env, cond)) != bool:
                raise EvalError("Not bool")
            if evalInEnv(env, cond) == True:
                return evalInEnv(env, thenexpr)
            else:
                return evalInEnv(env, elseexpr)
            
        case Letfun(n,p,b,i):
            c = Closure(p,b,env)
            loc = newLoc(c)
            newEnv = extendEnv(n,loc,env)
            c.env = newEnv        
            return evalInEnv(newEnv,i)
            #c = Closure(p,b,env)
            #newEnv = extendEnv(n,c,env)
            #c.env = newEnv        
            #return evalInEnv(newEnv,i)
        
        case App(f,a):
            fun = evalInEnv(env,f)
            arg = evalInEnv(env,a)
            match fun:
                case Closure(p,b,cenv):
                    argLoc = newLoc(arg)
                    newEnv = extendEnv(p,argLoc,cenv) 
                    return evalInEnv(newEnv,b)
                case _:
                    raise EvalError("application of non-function")
            #fun = evalInEnv(env,f)
            #arg = evalInEnv(env,a)
            #match fun:
            #    case Closure(p,b,cenv):
            #        newEnv = extendEnv(p,arg,cenv) 
            #        return evalInEnv(newEnv,b)
            #    case _:
            #        raise EvalError("application of non-function")
        
        case Assign(n, e):
            l = lookupEnv(n, env)
            if l is None:
                raise EvalError(f"unbound name {n}")
            v = evalInEnv(env, e)
            setLoc(l,v)

        case Seq(e1,e2):
            evalInEnv(env, e1)
            return evalInEnv(env, e2)
       
        case Show(e):
            e1 = e
            e2 = e
            v = evalInEnv(env, e1)
            match (v):
                case (Path(pl)):
                    run(e2)
                    return Path(pl)
                case _:
                    print(v)
                    return v

        case Read():
            user_input = input("Input: ")
            try:
                return int(user_input)
            except ValueError:
                raise EvalError("Input is not an integer")
        


def run(e: Expr) -> None:
    print(f"running {e}")
    try:
        match eval(e):
            case int(i):
                print(f"result: {i}")
            case Path(path):
                t.clearscreen()
                t.speed(10)
                for a in path:
                    match a:
                        case Forward(d):
                            t.forward(d)
                        case Left(a):
                            t.left(a)
                        case Back(b):
                            t.back(b)
                        case Right(r):
                            t.right(r)
                        case Color(c):
                            t.color(c)
                        case PenSize(p):
                            t.pensize(p)
                time.sleep(2)
    except EvalError as err:
        print(err)

#Some expressions to test out. The box and star expressions 
#were copied over from the Turtle interpreter example in class

box2: Expr = Rotate(Lit(45), Repeat(Lit(4), Append(Lit(Forward(100)), Lit(Left(90)))))

star: Expr = Repeat(Lit(36), Append(Lit(Forward(200)), Lit(Left(170))))

#circle: Expr = Repeat(Lit(360), Append(Lit(Forward(1)), Lit(Right(1)), Lit(Color(0))))
circle: Expr = Repeat(Lit(360), Append(Lit(Back(1)), Lit(Right(1))))

#hexagon: Expr = Repeat(Lit(6), Append(Lit(Color("red")), Lit(Back(100)), Lit(Right(60))))
hexagon: Expr = Repeat(Lit(6), Append(Lit(Back(100)), Lit(Right(60))))

colorhex: Expr = Repeat(Lit(3), Append(
                         Append(AddColor(Lit(Color("magenta")), Lit(Back(150))), Lit(Right(60))), 
                         Append(AddColor(Lit(Color("lime")), Lit(Back(150))), Lit(Right(60))))
                         )

bighex: Expr = Repeat(Lit(3), Append(
                         Append(SetSize(Lit(PenSize(5)), Lit(Back(150))), Lit(Right(60))), 
                         Append(SetSize(Lit(PenSize(10)), Lit(Back(150))), Lit(Right(60))))
                         )
test1: Expr = Eq(Lit(Forward(50)), Lit(Forward(50)))
test2: Expr = Eq(Lit(Forward(50)), Lit(Forward(150)))
test3: Expr = Eq(Lit(Left(50)), Lit(Left(50)))

"""
run(test1)
run(test2)
run(test3)
run(box2)
#run(star)
#run(circle)
run(hexagon)
run(colorhex)
run(bighex)

#t.mainloop()
t.done()
"""