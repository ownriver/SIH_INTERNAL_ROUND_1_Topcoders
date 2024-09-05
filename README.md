# Develop a Cloud-Integrated IoT Alarm Clock with Dashboard Integration

This README provides an overview of the project, including team details, relevant links, tasks completed, tech stack, key features, and steps to run the project locally.

We have created a fully functioning android application which is thereby integrated with the IoT web services which can be used to access the various functionalities on the Smart Alarm Clock remotely on the go.

## Team Details

**Team Name:** TEAM_Topcoders

**Team Leader:** [@ownriver](https://github.com/ownriver)

**Team Members:**

- Amaan Aijaz - 2023UCS1582 - [@ownriver](https://github.com/ownriver)
- Mohammad Asif - 2023UCS1610 - [@Zardari9](https://github.com/Zardari9)
- Khushi Monga - 2023UEC2584 - [@Khushi-monga](https://github.com/Khushi-monga)
- Ujjawal Kumar - 2023UCS1502 - [@UJJAWALX42](https://github.com/UJJAWALX42)
- Shukla Shukla - 2023UCD2156 - [@shuklaafk](https://github.com/shuklaafk)
- Mohammad Bilal - 2023UCS1638 - [@mohammadBilal03](https://github.com/mohammadBilal03)

## Project Links

- **Internal Presentation:** [Internal Presentation](https://github.com/ownriver/Team_Topcoders/blob/main/files/INTERNAL_PPT_Topcoders.pdf)
- **Final SIH Presentation:** [Final SIH Presentation](https://github.com/ownriver/Team_Topcoders/blob/main/files/SIH_PPT_Topcoders.pdf)
- **Video Demonstration:** [Watch Video](https://www.youtube.com/watch?v=sGwE_axStU8)
- **Source Code:** [GitHub Repository](https://github.com/mohammadBilal03/Clock_App)
- **Additional Resources:** [Other Relevant Links](https://github.com/ownriver/Team_Topcoders/tree/main/codes/Clock%20App)

--------------------------------------------------------------------------------------------------

**STEPS TO RUN CUSTOM MADE APPLICATION MADE USING REACT NATIVE FRAMEWORK & ANDROID STUDIO**

1. Open Android studios on your computer.
2. Click on the hamburger icon located at the top left corner .
3. Navigate to tools and select the Device Manager option.
4. Now, click on the Wifi Icon labelled as "Pair Devices Using Wifi".
5. You will see two options displayed:
       (a) Pair using QR Code.
       (b) Pair using Pairing Code.
6. On your mobile phone, go to Settings > Developer Options > Wireless Debugging 
7. Select the option in your  mobile which was chosen in Android studio to pair mobile with Android studio successfully.
8. It is now paired over Wifi.

Alternate method:

Simply connect your mobile phone to your computer through the USB, and you will be able to run the programs directly from Android Studio,
without the requirement of the additional setup.

---------------------------------------------------------------------------------------------------------
**STEPS TO RUN THE WEBSITE**

For Arduino Website & App, follow the steps given below: 

• Website 

1. Firstly, Go to cloud.arduino.cc 
2. ⁠sign in using the following username and password given below: 
-> username: glucond49@gmail.com
-> password: password@05
3. Thereafter, click on dashboard icon on the left sidebar 
4. ⁠ Click on Alarm_Clock_IoT 
You now have access to all the features of the IoT based alarm clock using the website. 

• Application 

1. Download the following application: Arduino IoT Cloud Remote 
2. ⁠sign in using the following username and password given below: 
-> username: glucond49@gmail.com
-> password: password@05
3. Thereafter, click on dashboard icon on the left sidebar 
4. ⁠ Click on Alarm_Clock_IoT 
You now have access to all the features of the IoT based alarm clock using the application.

-----------------------------------------------------------------------------------------------------------

**Tech Stacks Used**
- ### *Hardware*:
1. *Buzzer*
2. *Pushbuttons*
3. *LCD Module*
4. *I2C Converter*

### *Software*:
1. *Arduino IDE*
2. *IoT Web Service*: Arduino IoT Cloud
3. *Libraries Used*:
   - time.h
   - LiquidCrystal_I2C.h
   - ArduinoIoTCloud.h
   - Arduino_ConnectionHandler.h
4. *Web Services Used*:
   - RTC Servers: "pool.ntp.org", "time.nist.gov"
5. *React Native Framework* (with HTML, CSS, and JavaScript)
6. *Android Studio* (used for the emulator)
