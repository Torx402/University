using Microsoft.AspNetCore.Identity;

namespace Clinic.Data;

public class Users : IdentityUser<int>
{
    [PersonalData]
    public string? Name { get; set; }
}