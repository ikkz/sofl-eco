import { invoke } from '@tauri-apps/api';
import sum from 'lodash-es/sum';
import { EvaluateResult } from '@/types';

export async function getEvaluateResult(code: string) {
  const result: EvaluateResult = await invoke('evaluate', { sourceCode: code });
  const lines = code.split('\n').map(line => line.length + 1);
  result.diagnostics.forEach(({ range }) => {
    range.from =
      sum(lines.slice(0, range.start_point.row)) + range.start_point.column;
    range.to =
      sum(lines.slice(0, range.end_point.row)) + range.end_point.column;
  });
  result.type_details.forEach(({ range }) => {
    range.from =
      sum(lines.slice(0, range.start_point.row)) + range.start_point.column;
    range.to =
      sum(lines.slice(0, range.end_point.row)) + range.end_point.column;
  });
  return result;
}
