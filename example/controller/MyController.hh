<?hh
class MyController {

    public function barAction(HackMvc\Routing\RouteMatch $route_match, HackMvc\Service\Locator $service_locator) {
        return 'bar';
    }
    
}