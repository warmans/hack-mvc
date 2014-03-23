<?hh
namespace HackMvc\Http;

class Request {

	private string $raw_body = '';
	private array<string, string> $parsed_body = array();
	
	public function __construct(private \string $method, private Uri $uri, private \Map $headers)
	{}

	public function getMethod(): \string
	{
		return $this->method;
	}

	public function getUri(): Uri
	{
		return $this->uri;
	}

	public function setRawBody(\string $body): \void
	{
		$this->raw_body = $body;
	}

	public function getRawBody(): \string
	{
		return $this->raw_body;
	}

	public function getBody(): array
	{
		if (!$this->parsed_body) {
			parse_str($this->getRawBody(), $this->parsed_body);
		}
		return $this->parsed_body;
	}
}
