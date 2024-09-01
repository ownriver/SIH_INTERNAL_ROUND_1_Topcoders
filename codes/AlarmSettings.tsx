// AlarmSettings.js

import React, { useState } from 'react';
import {
  SafeAreaView,
  ScrollView,
  View,
  Text,
  TextInput,
  Button,
  TouchableOpacity,
  StyleSheet,
  Alert,
} from 'react-native';

const AlarmSettings = () => {
  const [alarmTime, setAlarmTime] = useState('');
  // const [selectedTone, setSelectedTone] = useState('Tone1');
  // const [audioPosition, setAudioPosition] = useState('0 sec');

  const setAlarm = () => {
    Alert.alert('Alarm set for', alarmTime);
  };

  const cancelAlarm = () => {
    setAlarmTime('');
    Alert.alert('Alarm cancelled');
  };

  // const applyTone = () => {
  //   Alert.alert('Selected Tone', selectedTone);
  // };

  const previewWallpaper = () => {
    Alert.alert('Preview Wallpaper', 'Previewing wallpaper...');
  };

  const purchaseWallpaper = () => {
    Alert.alert('Purchase Wallpaper', 'Wallpaper purchased successfully!');
  };

  return (
    <SafeAreaView style={styles.container}>
      <ScrollView contentContainerStyle={styles.scrollContainer}>
        <Text style={styles.header}>Alarm Settings</Text>

        {/* Add Alarm Section */}
        <TouchableOpacity style={styles.section}>
          <Text style={styles.sectionText}>Add Alarm</Text>
        </TouchableOpacity>

        {/* Set Wallpaper Section */}
        <TouchableOpacity style={styles.section} onPress={previewWallpaper}>
          <Text style={styles.sectionText}>Set Wallpaper</Text>
        </TouchableOpacity>

        {/* Set Ringtone Section
        <TouchableOpacity style={styles.section}>
          <Text style={styles.sectionText}>Set Ringtone</Text>
        </TouchableOpacity> */}

        {/* Buy Wallpapers Section */}
        <TouchableOpacity style={styles.section} onPress={purchaseWallpaper}>
          <Text style={styles.sectionText}>Buy Wallpapers</Text>
        </TouchableOpacity>

        {/* Make Your Own Wallpaper Section */}
        <TouchableOpacity style={styles.section}>
          <Text style={styles.sectionText}>Make your own wallpaper!</Text>
        </TouchableOpacity>

        {/* Alarm Time Section */}
        <View style={styles.alarmTimeContainer}>
          <Text style={styles.alarmHeader}>ALARM TIME</Text>
          <TextInput
            style={styles.input}
            placeholder="00:00"
            value={alarmTime}
            onChangeText={setAlarmTime}
          />
          <Button title="Set Alarm" onPress={setAlarm} />
          <Button title="Cancel" onPress={cancelAlarm} color="red" />
        </View>

        

        {/* Wallpaper Preview Section */}
        <TouchableOpacity style={styles.section} onPress={previewWallpaper}>
          <Text style={styles.sectionText}>CLICK TO PREVIEW</Text>
        </TouchableOpacity>

        {/* Dropbox Integration Placeholder */}
        <TouchableOpacity style={styles.section}>
          <Text style={styles.sectionText}>Link Dropbox Sync</Text>
        </TouchableOpacity>
      </ScrollView>
    </SafeAreaView>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#f0f0f0',
  },
  scrollContainer: {
    alignItems: 'center',
    padding: 20,
  },
  header: {
    fontSize: 24,
    fontWeight: 'bold',
    marginBottom: 20,
  },
  section: {
    backgroundColor: '#ffffff',
    width: '100%',
    padding: 15,
    marginBottom: 10,
    borderRadius: 8,
    elevation: 3,
    alignItems: 'center',
  },
  sectionText: {
    fontSize: 18,
    color: '#333',
  },
  alarmTimeContainer: {
    backgroundColor: '#ffffff',
    width: '100%',
    padding: 15,
    marginBottom: 10,
    borderRadius: 8,
    elevation: 3,
    alignItems: 'center',
  },
  alarmHeader: {
    fontSize: 18,
    fontWeight: 'bold',
    marginBottom: 10,
  },
  input: {
    width: '80%',
    borderWidth: 1,
    borderColor: '#ddd',
    padding: 10,
    borderRadius: 5,
    textAlign: 'center',
    marginBottom: 10,
  },
  // picker: {
  //   height: 50,
  //   width: '80%',
  // },
  // alarmToneContainer: {
  //   backgroundColor: '#ffffff',
  //   width: '100%',
  //   padding: 15,
  //   marginBottom: 10,
  //   borderRadius: 8,
  //   elevation: 3,
  //   alignItems: 'center',
  // },
});

export default AlarmSettings;
