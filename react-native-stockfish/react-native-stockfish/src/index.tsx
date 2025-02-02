import { NativeModules, Platform } from 'react-native';

const LINKING_ERROR =
  `The package 'react-native-stockfish' doesn't seem to be linked. Make sure: \n\n` +
  Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
  '- You rebuilt the app after installing the package\n' +
  '- You are not using Expo Go\n';

const Stockfish = NativeModules.StockfishRN
  ? NativeModules.StockfishRN
  : new Proxy(
      {},
      {
        get() {
          throw new Error(LINKING_ERROR);
        },
      }
    );

export function init(): Promise<null> {
  return Stockfish.init();
}

export function write(s: string): Promise<null> {
  return Stockfish.write(s);
}

export function read(): Promise<string> {
  let promise = Stockfish.read();
  return promise;
}
