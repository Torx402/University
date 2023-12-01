using Microsoft.AspNetCore.Mvc;
using System.Text.Encodings.Web;

namespace MvcMovie.Controllers
{
    public class HelloWorldController : Controller //HelloWorldController derived from Controller, you can think of this
    {                                              //as adding a place where you can navigate to using the URL
        // 
        // GET: /HelloWorld/

        public IActionResult Index() //website.com/HelloWorld lands in the index by default
        {
            return View(); //returns View associated with HelloWorld, returns HelloWorld.cshtml
        }

        // 
        // GET: /HelloWorld/Welcome/ 

        public IActionResult Welcome(string name, int numTimes = 1) //website.com/HelloWorld/Welcome
        {                                                           //You can pass arguments to this, adds arguments to viewdata associated with this view for example
            ViewData["Message"] = "Hello " + name;
            ViewData["NumTimes"] = numTimes;

            return View();
        }
    }
}