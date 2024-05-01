import { Alert, Button, Dropdown, List, Menu } from '@arco-design/web-react';
import { IconUpload, IconList } from '@arco-design/web-react/icon';
import { useAtomValue, useSetAtom } from 'jotai';
import { PredefinedButton } from './predefine-button';
import { templates } from '@/templates';
import { codeAtom, evaluateResultAtom } from '@/state';
import { TSRange } from '@/types';
import { AppEvent, emitter } from '@/event';

export const Panel = () => {
  const setCode = useSetAtom(codeAtom);
  const result = useAtomValue(evaluateResultAtom);

  return (
    <div className="px-4 overflow-y-auto">
      <div className="text-lg font-semibold mb-2 mt-6">编辑</div>
      <div>
        <Dropdown
          trigger="click"
          droplist={
            <Menu>
              {templates.map(({ name, code }) => (
                <Menu.Item key={name} onClick={() => setCode(code)}>
                  {name}
                </Menu.Item>
              ))}
            </Menu>
          }
        >
          <Button type="primary" icon={<IconList />}>
            模板
          </Button>
        </Dropdown>
        <Button className="ml-3" icon={<IconUpload />}>
          导入
        </Button>
        <PredefinedButton />
      </div>
      <div className="text-lg font-semibold mb-2 mt-6">诊断</div>
      <List
        loading={result.state === 'loading'}
        bordered={false}
        dataSource={result.state === 'hasData' ? result.data.diagnostics : []}
        render={item => (
          <div
            className="cursor-pointer"
            onClick={() => emitter.emit(AppEvent.SET_SELECTION, item.range)}
          >
            <Alert
              className="mb-2"
              content={
                <div>
                  {item.message}
                  <div className="text-xs text-gray-600">
                    {formatRange(item.range)}
                  </div>
                </div>
              }
              type={item.level.toLowerCase() as any}
            />
          </div>
        )}
      />
    </div>
  );
};

const formatRange = (range: TSRange) =>
  `行列 [${range.start_point.row + 1}, ${range.start_point.column}] 至 [${
    range.end_point.row + 1
  }, ${range.end_point.column}]`;
