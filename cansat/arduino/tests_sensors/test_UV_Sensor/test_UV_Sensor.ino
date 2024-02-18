int uv_ain=A1;
int ad_value;
void setup()
{
  pinMode(uv_ain,INPUT);
  Serial.begin(9600);
}
void loop()
{
  ad_value=analogRead(uv_ain);
  Serial.println(ad_value);
  if(ad_value>20)
  {
    Serial.println("UV up the standard");
  }
  else
  {
    Serial.println("UV down the standard");
  }
  delay(500);
}
