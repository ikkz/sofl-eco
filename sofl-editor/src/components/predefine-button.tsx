import { Button, Drawer } from '@arco-design/web-react';
import { IconCode } from '@arco-design/web-react/icon';
import { useAtom } from 'jotai';
import { useState } from 'react';
import CodeMirror, { EditorView } from '@uiw/react-codemirror';
import { githubLight } from '@uiw/codemirror-theme-github';
import { predefinedSymbol } from '@/state';
import { symbols } from '@/builtins';

export const PredefinedButton = () => {
  const [visible, setVisible] = useState(false);
  const [predefinedSymbols, setPredefinedSymbols] = useAtom(predefinedSymbol);
  return (
    <>
      <Button
        className="ml-3"
        icon={<IconCode />}
        onClick={() => setVisible(true)}
      >
        预定义
      </Button>
      <Drawer
        width={500}
        title={<span>预定义符号</span>}
        visible={visible}
        onOk={() => setVisible(false)}
        onCancel={() => setVisible(false)}
      >
        <div className="font-bold mb-2">用户自定义</div>
        <CodeMirror
          value={predefinedSymbols}
          theme={githubLight}
          onChange={setPredefinedSymbols}
          className="text-base"
          extensions={[EditorView.lineWrapping]}
        />
        <div className="font-bold mb-2 mt-4">系统内置（不可修改）</div>
        <CodeMirror
          editable={false}
          value={symbols}
          theme={githubLight}
          className="text-base"
          extensions={[EditorView.lineWrapping]}
        />
      </Drawer>
    </>
  );
};
