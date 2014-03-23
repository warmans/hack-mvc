# Hack MVC

Silex-style emicroframework written in hack for the purposes of me learning Hack.

```
//avoid direct access of PHP built-in globals
$globals = new \HackMvc\Php\Globals();

//create a HTTP request
$request = $globals->getHttpRequest();

//create a service locator
$sl = new HackMvc\Service\Locator();

//create an application using the service locator
$app = new HackMvc\Application($sl);

//add a GET handler
$app->get('#^/foo$#', function(HackMvc\Routing\RouteMatch $route_match, HackMvc\Service\Locator $service_locator) { 
    return new \HackMvc\Http\Response(new \HackMvc\Http\Status(200), new \Map(array('x-some-header'=>'blah')), 'foo'); 
});

//use a service to handle the request
$app->get('#^/bar$#', array($sl->getService('controller.bar'), 'handle'));

//get response
$response = $app->handle($request);

//flush headers and body
$response->flush();
```