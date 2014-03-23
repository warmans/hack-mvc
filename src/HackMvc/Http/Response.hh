<?hh
namespace HackMvc\Http;

class Response {

    public function __construct(private Status $status, private \Map $headers, private \string $body)
    {}

    public function flush()
    {
        //set HTTP status code
        header($this->status->toString());

        //set any other headers
        foreach($this->headers as $name => $value) {
            header("$name: $value");
        }

        echo $this->body;
    }
}
