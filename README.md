# ds1302

These are two small programms to read and write the register of a DS1302

## Usage

### Compile

```bash
make
```

### Write to Register

```bash
./setTime
```

### Read from Register

```bash
./getTime
```

## Hardware Setup

| DS1302  | Raspberry Pi | wiringPi |
|---------|--------------|----------|
| VCC2    |  5V          |          |
| GND     | Ground       |          |
| SCLK    | GPIO 23      | 4        |
| I/O     | GPIO 24      | 5        |
| CE      | GPIO         | 6        |


## Developer

* [Felix Knorre](felix-knorre@hotmail.de)

## Links

* [wiringPi](http://wiringpi.com/)

