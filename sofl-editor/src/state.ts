import { atom, createStore } from 'jotai';
import { loadable } from 'jotai/utils';
import { templates } from './templates';
import { getEvaluateResult } from './api';

export const codeAtom = atom(
  process.env.NODE_ENV === 'development' ? templates[0].code : '',
);

export const evaluateResultAtom = loadable(
  atom(async get => await getEvaluateResult(get(codeAtom))),
);

export const store = createStore();
