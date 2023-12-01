using System.ComponentModel.DataAnnotations;

namespace Clinic.Models
{   
    public class Doctor
    {
        private static readonly string[] specializations = ["Home", "ENT", "Dermatologist", "Ophthalmologist", "Neurologist", "Orthopedist", "Pediatrician"];
        public int ID { get; set; }

        [Required]
        [StringLength(100)]
        public string? Name { get; set; }
        private string? specialization;

        [Required]
        public string? Specialization
        {
            get { return specialization; }
            set { specialization = (value != null && specializations.Contains(value.ToString())) ? value : throw new ArgumentException("Invalid Specialization!"); }
        }

        [Required]
        public DateTime AvailabilityStart { get; set; }

        [Required]
        public DateTime AvailabilityEnd { get; set; }
    }
}