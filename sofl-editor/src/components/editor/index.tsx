import CodeMirror, {
  ReactCodeMirrorRef,
  EditorView,
  EditorSelection,
} from '@uiw/react-codemirror';
import { githubLight } from '@uiw/codemirror-theme-github';

import { useCallback, useEffect, useRef } from 'react';
import { useAtom } from 'jotai';

import { cursorTooltipBaseTheme, selectionTooltipField } from './extensions';
import { codeAtom } from '@/state';
import { AppEvent, emitter } from '@/event';
import { TSRange } from '@/types';

export const Editor = () => {
  const editorRef = useRef<ReactCodeMirrorRef>(null);
  const [code, setCode] = useAtom(codeAtom);

  const onChange = useCallback((newCode: string) => setCode(newCode), []);

  useEffect(() => {
    emitter.on(AppEvent.SET_SELECTION, (range: TSRange) => {
      const view = editorRef.current?.view;
      if (view) {
        view.dispatch({
          selection: EditorSelection.create([
            EditorSelection.range(range.from, range.to),
          ]),
        });
      }
    });
  }, []);

  return (
    <CodeMirror
      key="editor"
      value={code}
      onChange={onChange}
      theme={githubLight}
      className="text-base h-full"
      ref={editorRef}
      extensions={[
        cursorTooltipBaseTheme,
        selectionTooltipField,
        EditorView.lineWrapping,
      ]}
    />
  );
};
