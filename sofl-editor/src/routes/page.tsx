import './index.css';

import { ResizeBox } from '@arco-design/web-react';
import { Editor } from '@/components/editor';
import { Panel } from '@/components/panel';

const Index = () => (
  <ResizeBox.Split
    direction="horizontal"
    size={0.7}
    max={0.8}
    min={0.2}
    className="h-full w-full"
    panes={[<Editor key="editor" />, <Panel key="panel" />]}
  />
);

export default Index;
