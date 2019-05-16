// Aviya Goldfarb 201509635
// Yehoshua Lipsker 204038533
// Fetch prints the content found at each specified URL.
package main

import (
	"fmt"
	"io"
	"net/http"
	"os"
	"strings"
)

func checkPrefix(url string) string {
	if !strings.HasPrefix(url, "http://") &&
		!strings.HasPrefix(url, "https://") {
		url = "http://" + url
	}
	return url
}

func main() {
	for _, url := range os.Args[1:] {

		// Exercise 1.1
		url = checkPrefix(url)
		resp, err := http.Get(url)
		if err != nil {
			fmt.Fprintf(os.Stderr, "fetch: %v\n", err)
			os.Exit(1)
		}

		// Exercise 1.3
		fmt.Fprintf(os.Stdout, "resp.status %s\n", resp.Status)

		// Exercise 1.2
		_, err = io.Copy(os.Stdout, resp.Body)
		resp.Body.Close()
		if err != nil {
			fmt.Fprintf(os.Stderr, "fetch: reading %s: %v\n", url, err)
			os.Exit(1)
		}
	}
}
