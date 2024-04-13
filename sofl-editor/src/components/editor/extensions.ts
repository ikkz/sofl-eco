import {
  EditorState,
  SelectionRange,
  StateField,
  Tooltip,
  showTooltip,
  EditorView,
} from '@uiw/react-codemirror';

import identity from 'lodash-es/identity';
import { evaluateResultAtom, store } from '@/state';

const shrinkRange = (range: SelectionRange, state: EditorState) => {
  const text = state.doc.sliceString(range.from, range.to);
  const leadingSkip = text.match(/^\s*/)?.[0]?.length;
  const trailingSkip = text.match(/\s*$/)?.[0]?.length;
  return {
    from: range.from + (leadingSkip || 0),
    to: range.to - (trailingSkip || 0),
  };
};

const getSelectionTooltips = (state: EditorState): readonly Tooltip[] => {
  const result = store.get(evaluateResultAtom);
  if (result.state === 'hasData') {
    return state.selection.ranges
      .map(range => shrinkRange(range, state))
      .filter(({ from, to }) => from !== to)
      .map(range => {
        const { from, to } = range;
        const type_detail = result.data.type_details.find(
          ({ range }) => range.from === from && range.to === to,
        );
        return (
          type_detail
            ? {
                pos: range.to,
                create: () => {
                  const dom = document.createElement('div');
                  dom.className = 'cm-tooltip-cursor font-mono';
                  const typeStr = document.createElement('div');
                  typeStr.textContent = type_detail.type_str;
                  dom.appendChild(typeStr);
                  if (type_detail.type_expanded !== type_detail.type_str) {
                    const typeExpanded = document.createElement('div');
                    typeExpanded.textContent = `Expanded: ${type_detail.type_expanded}`;
                    dom.appendChild(typeExpanded);
                  }
                  return { dom };
                },
              }
            : null
        ) as Tooltip;
      })
      .filter(identity);
  }
  return [];
};

export const selectionTooltipField = StateField.define<readonly Tooltip[]>({
  create: getSelectionTooltips,
  update(tooltips, tr) {
    if (!tr.docChanged && !tr.selection) {
      return tooltips;
    }
    return getSelectionTooltips(tr.state);
  },
  provide: f => showTooltip.computeN([f], state => state.field(f)),
});

export const cursorTooltipBaseTheme = EditorView.baseTheme({
  '.cm-tooltip.cm-tooltip-cursor': {
    backgroundColor: 'rgb(var(--primary-5))',
    color: 'white',
    border: 'none',
    padding: '2px 7px',
    borderRadius: '4px',
  },
});
