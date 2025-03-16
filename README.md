**Purpose of the Assignment**
<To get student familiar with using embedded electronics as a web client to consume apis>

**Summary**
<if(WiFi.status() == WL_CONNECTED)> <check to see if WiFi is connected>

<HTTPClient http
http.begin(ENDPOINT);
http.addHeader("api-key", apiKey)  <establish connection with the api>

<serializeJson(object, request_body)> <create a document or container for the message to be received>

<int responseCode = http.GET(); 
save the HTTP response in a variable>

<if (responseCode <= 0){...}> <Check to see if the response is an error. If it is, return to the begin to re-establish a connection>

<String response = http.getString()> <Get the message in the form of a string>

<http.end()> <Ends the http connection>

<DeserializationError error = deserializeJson(object,response)> <Convert string to an object. If conversion failed, an error value is saved in "error">

<if(error)> <Check to see if there is an error in conversion. If there is, print there was a deserialization error and return to the top of the void loop.>

<String line_1 = object["line1"]
String line_2 = object["line2"]> <Extract line 1 and line 2>

<lcd.setCursor(0, 0);>   <Start at the first row>
<lcd.print("Line1: ");> 
<lcd.print(line_1);>  <Prints line 1 on LCD>
<lcd.setCursor(0, 1);>  <Move to second row>
<lcd.print("Line2: ");>
<lcd.print(line_2);> <Prints line 2 on LCD>

**Riddle**
<I have four legs in the morning, two legs in the afternoon and three legs at night, what am I?>