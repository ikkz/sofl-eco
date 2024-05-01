// Prevents additional console window on Windows in release, DO NOT REMOVE!!
#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

use std::collections::HashMap;

use sofl_type_checker::EvaluateResult;

#[tauri::command]
fn evaluate(source_code: String, predefined_symbols: Vec<String>) -> EvaluateResult {
    sofl_type_checker::evaluate_type(
        source_code,
        predefined_symbols
            .into_iter()
            .rev()
            .fold(HashMap::new(), |mut map, code| {
                map.extend(sofl_type_checker::collect_symbols(code));
                map
            }),
    )
}

fn main() {
    tauri::Builder::default()
        .invoke_handler(tauri::generate_handler![evaluate])
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}
