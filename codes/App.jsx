import React, { useState, useEffect } from 'react';
import { View, Text, TextInput, Button, StyleSheet, Alert } from 'react-native';

const App = () => {
  const [currentTime, setCurrentTime] = useState('');
  const [alarmTime, setAlarmTime] = useState('');
  const [alarmSet, setAlarmSet] = useState(false);

  // Function to get and format the current time
  const updateTime = () => {
    const time = new Date().toLocaleTimeString('en-US', { hour12: false });
    setCurrentTime(time);
  };

  // Update the time every second
  useEffect(() => {
    const timer = setInterval(updateTime, 1000);
    return () => clearInterval(timer);
  }, []);

  // Check if the alarm time is reached
  useEffect(() => {
    if (alarmSet && currentTime === alarmTime) {
      Alert.alert('Alarm', 'Wake up! It\'s time!');
      setAlarmSet(false);
    }
  }, [currentTime, alarmTime, alarmSet]);

  // Handle setting the alarm
  const handleSetAlarm = () => {
    if (alarmTime) {
      setAlarmSet(true);
      Alert.alert('Alarm Set', `Alarm is set for ${alarmTime}`);
    } else {
      Alert.alert('Error', 'Please enter a valid time.');
    }
  };

  return (
    <View style={styles.container}>
      <Text style={styles.title}>Simple Alarm Clock</Text>
      <View style={styles.clockContainer}>
        <Text style={styles.clockText}>{currentTime}</Text>
      </View>
      <TextInput
        style={styles.input}
        placeholder="Set alarm (HH:MM:SS)"
        placeholderTextColor="#999"
        value={alarmTime}
        onChangeText={setAlarmTime}
        keyboardType="numeric"
      />
      <View style={styles.buttonContainer}>
        <Button title="Set Alarm" onPress={handleSetAlarm} color="#6200ee" />
      </View>
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#282c34',
  },
  title: {
    fontSize: 32,
    color: '#ffffff',
    marginBottom: 20,
    fontWeight: 'bold',
  },
  clockContainer: {
    backgroundColor: '#444',
    padding: 20,
    borderRadius: 10,
    marginBottom: 30,
    shadowColor: '#000',
    shadowOffset: { width: 0, height: 4 },
    shadowOpacity: 0.3,
    shadowRadius: 5,
    elevation: 10,
  },
  clockText: {
    fontSize: 48,
    color: '#00ff00',
    fontWeight: 'bold',
  },
  input: {
    height: 40,
    borderColor: '#6200ee',
    borderWidth: 2,
    width: '80%',
    marginBottom: 20,
    paddingHorizontal: 10,
    color: '#ffffff',
    backgroundColor: '#333',
    borderRadius: 5,
  },
  buttonContainer: {
    width: '80%',
    borderRadius: 5,
    overflow: 'hidden',
  },
});

export default App;
