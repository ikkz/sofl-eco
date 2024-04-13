import Emittery from 'emittery';

export enum AppEvent {
  'SET_SELECTION' = 'SET_SELECTION',
}

export const emitter = new Emittery();
