int PIN_BLUE = 3;                   // blue color at pin 3
int PIN_GREEN = 5;                  // green color at pin 5
int PIN_RED = 6;                    // red color at pin 6
int counter = 0;
int numColors = 255;
int animationDelay = 10;

void setup() 
{
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    digitalWrite(PIN_RED, 1);
    delay(1000);
    digitalWrite(PIN_RED, 0);
    digitalWrite(PIN_GREEN, 1);
    delay(1000);
    digitalWrite(PIN_GREEN, 0);
    digitalWrite(PIN_BLUE, 1);
    delay(1000);
    digitalWrite(PIN_BLUE, 0);
}
 
void loop() 
{
    float colorNumber = counter > numColors ? counter - numColors: counter;
    float saturation = 1;                                          // Between 0 and 1 (0 = gray, 1 = full color)
    float brightness = .05;                                        // Between 0 and 1 (0 = dark, 1 is full brightness)
    float hue = (colorNumber / float(numColors)) * 360;            // Number between 0 and 360
    long color = HSBtoRGB(hue, saturation, brightness);
    int red = color >> 16 & 255;
    int green = color >> 8 & 255;
    int blue = color & 255;

    setColor(red, green, blue);
    
    counter = (counter + 1) % (numColors * 2);
    
    // counter = (counter + 1) % (numColors);

    delay(animationDelay);
}

void setColor (unsigned char red, unsigned char green, unsigned char blue)
{       
    analogWrite(PIN_RED, red);
    analogWrite(PIN_GREEN, green);
    analogWrite(PIN_BLUE, blue);
    }

long HSBtoRGB(float _hue, float _sat, float _brightness) 
{
    float red = 0.0;
    float green = 0.0;
    float blue = 0.0;
   
    if (_sat == 0.0) {
        red = _brightness;
        green = _brightness;
        blue = _brightness;
    } else {
        if (_hue == 360.0) {
            _hue = 0;
        }

        int slice = _hue / 60.0;
        float hue_frac = (_hue / 60.0) - slice;

        float aa = _brightness * (1.0 - _sat);
        float bb = _brightness * (1.0 - _sat * hue_frac);
        float cc = _brightness * (1.0 - _sat * (1.0 - hue_frac));
        
        switch(slice) {
            case 0:
                red = _brightness;
                green = cc;
                blue = aa;
                break;
            case 1:
                red = bb;
                green = _brightness;
                blue = aa;
                break;
            case 2:
                red = aa;
                green = _brightness;
                blue = cc;
                break;
            case 3:
                red = aa;
                green = bb;
                blue = _brightness;
                break;
            case 4:
                red = cc;
                green = aa;
                blue = _brightness;
                break;
            case 5:
                red = _brightness;
                green = aa;
                blue = bb;
                break;
            default:
                red = 0.0;
                green = 0.0;
                blue = 0.0;
                break;
        }
    }
    long ired = red * 255.0;
    long igreen = green * 255.0;
    long iblue = blue * 255.0;
    return long((ired << 16) | (igreen << 8) | (iblue));
}
