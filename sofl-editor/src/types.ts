export interface Point {
  row: number;
  column: number;
}

export interface TSRange {
  start_point: Point;
  end_point: Point;
  from: number;
  to: number;
}

export interface Diagnostic {
  level: 'Error' | 'Warning' | 'Info';
  message: string;
  range: TSRange;
}

export interface TypeDetail {
  range: TSRange;
  source: string;
  type_expanded: string;
  type_str: string;
}

export interface EvaluateResult {
  diagnostics: Diagnostic[];
  type_details: TypeDetail[];
}
