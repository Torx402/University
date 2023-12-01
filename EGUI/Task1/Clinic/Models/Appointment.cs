using System.ComponentModel.DataAnnotations;

namespace Clinic.Models
{
    public enum AppointmentStatus
    {
        Completed,
        Scheduled,
        Cancelled
    }

    public class Appointment 
    {
        public int ID { get; set; }

        [Required]
        public int DoctorID { get; set; }

        [Required]
        public int PatientID { get; set; }

        [Required]
        public DateTime AppointmentDateTime { get; set; }

        [Required]
        public AppointmentStatus Status { get; set; }

        public virtual Doctor? Doctor { get; set; }
        public virtual Patient? Patient { get; set; }
    }
}