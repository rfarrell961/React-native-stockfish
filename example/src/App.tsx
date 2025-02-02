import * as React from 'react';

import { StyleSheet, View, Text, Button, TextInput, NativeEventEmitter, NativeModules } from 'react-native';
import { init, write, read } from 'react-native-stockfish';

const { StockfishRN } = NativeModules;
const eventEmitter = new NativeEventEmitter(StockfishRN);

export default function App() {
  const [writeVal, setWriteVal] = React.useState<string>();

  React.useEffect(() => {
    init(); 
  }, []);

  return (
    <View style={styles.container}>
      
      <View style={{flexDirection: 'row', flex: 1, marginTop: 50}}>
        <TextInput editable
        multiline
        numberOfLines={4}
        maxLength={40}
        autoCapitalize='none'
        style={{borderColor:"black", borderWidth:1, width:250, height:400}}
        onChangeText={text => setWriteVal(text)}
        value={writeVal}></TextInput>
        <Button title='Write' onPress={() => {
          write(writeVal ? writeVal : ' ');
        }}></Button>
      </View>
      <View style={{flexDirection: 'row'}}>
        <Button title='Read' onPress={async () => {
          let s = await read();
          console.log(s);
        }}></Button>
      </View>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
  },
  box: {
    width: 60,
    height: 60,
    marginVertical: 20,
  },
});
