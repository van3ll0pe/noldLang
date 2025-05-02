The noldLang is a simple language in construction

## key word :

- fun (create function)
- var (create variable)
- if
- elsif
- else
- match
- case
- default
- while
- for
- loop (continue in c)
- break
- return

type:

- bool (true, false)
- u8
- i8
- u16
- i16
- u32
- i32
- u64
- i64

operation:

- (+) (plus)
- (-) (minus)
- (%) (modulo)
- (/) (division)
- (*) (times)

comparaison:

- (==) (equality)
- (/=) (inequality)
- (>) (greater than)
- (>=) (greater or equal)
- (<) (less than)
- (<=) (less or equal)

next to add:

- binary operation (and, or, xor, not, bit shift)
- logic operation (logic and, logic or, logic not)
- constant
- pointer
- enum
- structure

## examples :

create function

```
fun [name](parameter: type, parameter: type) : type function {
  ...
  return value_of_type;
}

fun [name](parameter: type, parameter: type) : void {
  ...
  return; //optional
}

fun add(a: u8, n:u8): i16 {
    var b: u8 = 43;
    return (i16)(a - b * n);
    
}
```

create variable
```
var name: type; //initialized with default value (0)
var name: type = value;
```

create loop
```
for (var i: u8 = 0; i < 10; i++) {
}

while(i < 10) {
}
```

statement
```
if (condition) {
}
elsif (condition) { //optional
}
else { //optional
}

if (a <= b) {
  code;
}

if (a /= b) {
  code;
}

match (condition or value) {
  case value: {code},
  case value_1: {code},
  case value_2: {code},
  default: {code}  //optional if all value of the condition of value is explicitly done
}
```


