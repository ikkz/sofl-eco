package tree_sitter_sofl_test

import (
	"testing"

	tree_sitter "github.com/smacker/go-tree-sitter"
	"github.com/tree-sitter/tree-sitter-sofl"
)

func TestCanLoadGrammar(t *testing.T) {
	language := tree_sitter.NewLanguage(tree_sitter_sofl.Language())
	if language == nil {
		t.Errorf("Error loading Sofl grammar")
	}
}
