package main 


import(
	"fmt"
	"log"
	"net/http"
)


func main() {
	http.HandleFunc("/b", func(w http.ResponseWriter, r *http.Request) {
		fmt.Fprintf(w, "B is OK :)"
	})


	log.Println("HTTP server B startup 5012")
	http.ListenAndServe(":5012", nil)
}