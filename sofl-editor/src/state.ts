import { atom, createStore } from 'jotai';
import { loadable, atomWithStorage } from 'jotai/utils';
import { templates } from './templates';
import { getEvaluateResult } from './api';
import { symbols } from './builtins';

export const codeAtom = atom(
  process.env.NODE_ENV === 'development' ? templates[0].code : '',
);

export const predefinedSymbol = atomWithStorage(
  'predefinedSymbols',
  'module ExternalSymbols;',
);

export const evaluateResultAtom = loadable(
  atom(
    async get =>
      await getEvaluateResult(get(codeAtom), [symbols, get(predefinedSymbol)]),
  ),
);

export const store = createStore();
