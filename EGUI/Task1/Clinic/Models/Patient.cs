using System.ComponentModel.DataAnnotations;

namespace Clinic.Models
{
    public class Patient 
    {
        public int ID { get; set; }
        
        [Required]
        [StringLength(100)]
        public string? Name{ get; set; }

        public bool active {get; set;}
    }
}